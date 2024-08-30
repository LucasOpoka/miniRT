/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:52:06 by atorma            #+#    #+#             */
/*   Updated: 2024/08/28 18:40:21 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../libft/libft.h"
#include <math.h>


uint32_t used = 1;

void	node_print_entry(t_node *node);
void	node_print_full(t_node *node, t_void_arr *shapes, int axis, float split_pos);

void	node_min_max(float *to_min, float *to_max, float *min, float *max);
float	node_cost(t_node *node);

void	sphere_bounds(float *min, float *max, t_shape *sphere);
void	cylinder_bounds(float *min, float *max, t_shape *cylinder);
void	shape_bounds_update(t_node *node, t_shape *shape);

void	float_set(float *f, float value)
{
	f[0] = value;
	f[1] = value;
	f[2] = value;
}

void	bvh_update_bounds(t_node *root, uint32_t index, t_scene *scene)
{
	t_node	    *node = &root[index];
	t_shape	    *shape;
	size_t	    i;

	i = 0;
	float_set(node->min, FLT_MAX);
	float_set(node->max, FLT_MIN);

	while (i < node->count)
	{
		shape = scene->shapes.arr[scene->bvh_index[node->first_index+ i]];
		shape_bounds_update(node, shape);
		i++;
	}
}


void	swap_qsort(uint32_t *shape_index, int i, int j)
{
	uint32_t    tmp;

	tmp = shape_index[i];
	shape_index[i] = shape_index[j];
	shape_index[j] = tmp;
}

t_split	find_best_split(t_node *node, t_scene *scene);

uint32_t    node_partition(t_node *node, t_scene *scene, t_split split,
		uint32_t *left_count, uint32_t *right_count)
{
	int i = node->first_index;
	int j = node->count + i - 1;
	t_shape	    *shape;

	while (i <= j)
	{
		shape = scene->shapes.arr[scene->bvh_index[i]];
		if (shape->centroid[split.axis] < split.pos)
		{
			*left_count += 1;
			i++;
		}
		else
		{
			swap_qsort(scene->bvh_index, i, j--);
			*right_count += 1;
		}
	}
	return (i);
}

void	bvh_subdivide(t_node *root, uint32_t index, t_scene *scene)
{
	t_node	*node = &root[index];
	const float no_split_cost = node_cost(node);
	t_split	split;

	split = find_best_split(node, scene);
	if (split.cost >= no_split_cost)
		return ;

	printf("no_split_cost: %f, split.cost: %f, split.pos: %f, split.axis: %d\n",
			no_split_cost, split.cost, split.pos, split.axis);

	uint32_t    left_count = 0;
	uint32_t    right_count = 0;
	uint32_t i = node_partition(node, scene, split, &left_count, &right_count);
	if (!left_count || !right_count)
		return ;
	printf("left_count: %d, right_count: %d\n", left_count, right_count);
	int left_index = used++;
	int right_index  = used++;
	root[left_index].first_index = node->first_index;
	root[left_index].count = left_count;
	root[right_index].first_index = i;
	root[right_index].count = right_count;
	node->left = left_index;
	//node->right can later be removed as it is not used anymore
	node->right = right_index;
	//Node that we have split the count should be set to 0
	node->count = 0;

	bvh_update_bounds(root, left_index, scene);
	bvh_update_bounds(root, right_index, scene);
	bvh_subdivide(root, left_index, scene);
	bvh_subdivide(root, right_index, scene);
}

long long	time_ms(void);

t_node	*bvh_build(t_scene *scene)
{
	uint32_t    i;
	t_node	    *root;
	uint32_t    *bvh_index;

	root = ft_calloc(1, (scene->shapes.i * 2 * sizeof(t_node)));
	bvh_index = ft_calloc(1, (scene->shapes.i * sizeof(uint32_t)));
	if (!root || !bvh_index)
	{
		free(root);
		free(bvh_index);
		return (NULL);
	}
	scene->bvh_root = root;
	scene->bvh_index = bvh_index;
	root->count = scene->shapes.i;
	i = 0;
	while (i < root->count)
	{
		scene->bvh_index[i] = i;
		t_shape *shape = scene->shapes.arr[i];
		shape->centroid[0] = shape->position.x;
		shape->centroid[1] = shape->position.y;
		shape->centroid[2] = shape->position.z;
		i++;
	}
	long long ms_start = time_ms();
	bvh_update_bounds(root, 0, scene);
	bvh_subdivide(root, 0, scene);
	long long ms_end = time_ms();
	printf("bhv_build took: %lldms\n", ms_end - ms_start);
	return (root);
}
