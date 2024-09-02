/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:52:24 by atorma            #+#    #+#             */
/*   Updated: 2024/08/31 17:18:50 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <math.h>

void	swap_obj(uint32_t *obj_index, int i, int j);

double	node_cost(t_node *node)
{
	double	ext[3];
	double	area;

	ext[0] = node->bounds.max[0] - node->bounds.min[0];
	ext[1] = node->bounds.max[1] - node->bounds.min[1];
	ext[2] = node->bounds.max[2] - node->bounds.min[2];
	area = ext[0] * ext[1] + ext[1] * ext[2] + ext[2] * ext[0];
	return (node->count * area);
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
			swap_obj(scene->bvh_index, i, j--);
	}
	return (i);
}
