/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:52:06 by atorma            #+#    #+#             */
/*   Updated: 2024/09/01 15:48:27 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../libft/libft.h"
#include <math.h>


uint32_t nodes_used = 1;

void	bounds_update(t_node *node, t_obj *obj);
double	node_cost(t_node *node);

void	obj_bounds_update(t_node *node, t_obj *obj);
void	bounds_init(t_bounds *bounds);
void	swap_qsort(uint32_t *obj_index, int i, int j);
t_split	find_best_split(t_node *node, t_scene *scene);

void	bvh_update_bounds(t_node *root, uint32_t index, t_scene *scene)
{
	t_node	    *node = &root[index];
	t_obj	    *obj;
	size_t	    i;

	i = 0;
	bounds_init(&node->bounds);
	while (i < node->count)
	{
		obj = scene->objs.arr[scene->bvh_index[node->first_index+ i]];
		bounds_update(node, obj);
		i++;
	}
}

uint32_t    node_partition(t_node *node, t_scene *scene, t_split split,
		uint32_t *left_count)
{
	int i = node->first_index;
	int j = node->count + i - 1;
	t_obj	    *obj;

	while (i <= j)
	{
		obj = scene->objs.arr[scene->bvh_index[i]];
		if (obj->centroid[split.axis] < split.pos)
		{
			*left_count += 1;
			i++;
		}
		else
		{
			swap_qsort(scene->bvh_index, i, j--);
		}
	}
	return (i);
}

int	bvh_split(t_node *root, t_node *node, t_split split, t_scene *scene)
{
	int	    left_index;
	uint32_t    left_count = 0;
	uint32_t    right_count;
	uint32_t    i;

	i = node_partition(node, scene, split, &left_count);
	if (!left_count || left_count == node->count)
		return (-1);
	right_count = node->count - left_count;
	(void) right_count; // Not used?
	left_index = nodes_used;
	//Split node must have obj count set to 0 !
	root[left_index].first_index = node->first_index;
	root[left_index].count = left_count;
	//node->right always is left_index + 1
	root[left_index + 1].first_index = i;
	root[left_index + 1].count = node->count - left_count;

	node->left = nodes_used;
	node->count = 0;
	nodes_used += 2;
	return (left_index);
}

void	bvh_subdivide(t_node *root, uint32_t index, t_scene *scene)
{
	t_node	    *node = &root[index];
	const double no_split_cost = node_cost(node);
	t_split	    split;
	int	    left_index;

	split = find_best_split(node, scene);
	if (split.cost >= no_split_cost)
		return ;

	printf("no_split_cost: %f, split.cost: %f, split.pos: %f, split.axis: %d\n",
			no_split_cost, split.cost, split.pos, split.axis);
	left_index = bvh_split(root, node, split, scene);
	if (left_index <= 0)
		return ;
	bvh_update_bounds(root, left_index, scene);
	bvh_update_bounds(root, left_index + 1, scene);
	bvh_subdivide(root, left_index, scene);
	bvh_subdivide(root, left_index + 1, scene);
}

long long	time_ms(void);

void	set_centroids(t_node *root, t_scene *scene)
{
	uint32_t    i;

	i = 0;
	while (i < scene->objs.i)
	{
		t_obj *obj = scene->objs.arr[i];
		if (obj->type != t_plane)
		{
			scene->bvh_index[root->count] = i;
			t_obj *obj = scene->objs.arr[i];
			obj->centroid[0] = obj->pos.x;
			obj->centroid[1] = obj->pos.y;
			obj->centroid[2] = obj->pos.z;
			root->count++;
		}
		i++;
	}
}

t_node	*bvh_build(t_scene *scene)
{
	t_node	    *root;
	uint32_t    *bvh_index;

	root = ft_calloc(1, (scene->objs.i * 2 * sizeof(t_node)));
	bvh_index = ft_calloc(1, (scene->objs.i * sizeof(uint32_t)));
	if (!root || !bvh_index)
	{
		free(root);
		free(bvh_index);
		return (NULL);
	}
	scene->bvh_root = root;
	scene->bvh_index = bvh_index;
	set_centroids(root, scene);
	long long ms_start = time_ms();
	bvh_update_bounds(root, 0, scene);
	bvh_subdivide(root, 0, scene);
	long long ms_end = time_ms();
	printf("bhv_build took: %lldms, node struct size: %lu\n",
			ms_end - ms_start, sizeof(t_node));
	return (root);
}
