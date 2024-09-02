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
#include "../../includes/bvh.h"
#include <math.h>


long long	time_ms(void);

void	    init_centroids(t_node *root, t_scene *scene);
void	    bounds_update(t_node *node, t_obj *obj);
double	    node_cost(t_node *node);
uint32_t    node_partition(t_node *node, t_scene *scene, t_split split,
		uint32_t *left_count);
void	    obj_bounds_update(t_node *node, t_obj *obj);
void	    bounds_init(t_bounds *bounds);
t_split	    find_best_split(t_node *node, t_scene *scene);

void	bvh_update_bounds(t_node *root, uint32_t index, t_scene *scene)
{
	t_node	    *node = &root[index];
	t_obj	    *obj;
	uint32_t    obj_index;
	size_t	    i;

	i = 0;
	bounds_init(&node->bounds);
	while (i < node->count)
	{
		obj_index = scene->bvh.i[node->first_index + i];
		obj = scene->objs.arr[obj_index];
		bounds_update(node, obj);
		i++;
	}
}

int	bvh_split(t_node *root, t_node *node, t_split split, t_scene *scene)
{
	int	    left_index;
	uint32_t    left_count = 0;
	uint32_t    i;

	i = node_partition(node, scene, split, &left_count);
	if (!left_count || left_count == node->count)
		return (-1);
	left_index = scene->bvh.nodes_used;
	root[left_index].first_index = node->first_index;
	root[left_index].count = left_count;
	//node->right always is left_index + 1
	root[left_index + 1].first_index = i;
	root[left_index + 1].count = node->count - left_count;

	node->left = left_index;
	//Split node must have obj count set to 0 !
	node->count = 0;
	scene->bvh.nodes_used += 2;
	return (left_index);
}

void	bvh_subdivide(t_node *root, uint32_t index, t_scene *scene)
{
	t_node	    *node = &root[index];
	const double no_split_cost = node_cost(node);
	t_split	    split;
	int	    left_index;

	if (index > BVH_MAX_NODES || node->count <= BVH_MIN_CHILDREN)
		return ;
	split = find_best_split(node, scene);
	if (split.cost >= no_split_cost)
		return ;

	printf("i: %u, no_split_cost: %f, split.cost: %f, split.pos: %f, split.axis: %d\n",
			index, no_split_cost, split.cost, split.pos, split.axis);
	left_index = bvh_split(root, node, split, scene);
	if (left_index <= 0)
		return ;
	bvh_update_bounds(root, left_index, scene);
	bvh_update_bounds(root, left_index + 1, scene);
	bvh_subdivide(root, left_index, scene);
	bvh_subdivide(root, left_index + 1, scene);
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
	scene->bvh.nodes_used = 1;
	scene->bvh.root = root;
	scene->bvh.i = bvh_index;
	init_centroids(root, scene);
	long long ms_start = time_ms();
	bvh_update_bounds(root, 0, scene);
	bvh_subdivide(root, 0, scene);
	long long ms_end = time_ms();
	printf("BVH build took: %lldms\nBVH node count: %u\nBVH node struct size: %lu\n",
			ms_end - ms_start, scene->bvh.nodes_used, sizeof(t_node));
	return (root);
}
