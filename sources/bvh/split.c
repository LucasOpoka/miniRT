/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:31:32 by atorma            #+#    #+#             */
/*   Updated: 2024/08/31 16:33:50 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../libft/libft.h"
#include <math.h>

void	float_set(float *f, float value);
void	obj_bounds_min_max(float *to_min, float *to_max, t_obj *obj);

/*
//Plane is split along the longest axis, not used anymore this is bad
float bvh_split_plane_old(t_node *node)
{
	float	split_pos;
	float	extent[3];
	int	axis;

	axis = 0;
	extent[0] = node->max[0] - node->min[0];
	extent[1] = node->max[1] - node->min[1];
	extent[2] = node->max[2] - node->min[2];
	if (extent[1] > extent[0])
		axis = 1;
	if (extent[2] > extent[axis])
		axis = 2;
	split_pos = node->min[axis] + extent[axis] * 0.5f;
	return (split_pos);
}
*/

float	area(t_bounds bounds, uint32_t	count)
{
	float	extent[3];
	float	area;

	extent[0] = bounds.max[0] - bounds.min[0];
	extent[1] = bounds.max[1] - bounds.min[1];
	extent[2] = bounds.max[2] - bounds.min[2];
	area = extent[0] * extent[1] + extent[1] * extent[2] + extent[2] * extent[0];
	return (count * area);
}

void	bounds_init(t_bounds *bounds)
{
	float_set(bounds->min, FLT_MAX);
	float_set(bounds->max, FLT_MIN);
}

float	evaluate_cost(t_node *node, t_split current, t_scene *scene)
{
	uint32_t    left_count = 0;
	uint32_t    right_count = 0;
	uint32_t    i = 0;
	t_bounds    left;
	t_bounds    right;

	bounds_init(&left);
	bounds_init(&right);
	while (i < node->count)
	{
		t_obj *obj = scene->objs.arr[scene->bvh_index[node->first_index + i]];
		if (obj->centroid[current.axis] < current.pos)
		{
			obj_bounds_min_max(left.min, left.max, obj);
			left_count++;
		}
		else
		{
			obj_bounds_min_max(right.min, right.max, obj);
			right_count++;
		}
		i++;
	}
	return (area(left, left_count) + area(right, right_count));
}


void	update_cost(t_split *best, t_split *current)
{
	if (current->cost <= 0)
		return ;
	if (current->cost < best->cost)
	{
		best->pos = current->pos;
		best->axis = current->axis;
		best->cost = current->cost;
	}
}

t_split	find_best_split(t_node *node, t_scene *scene)
{
	t_split	    best;
	t_split	    current;
	uint32_t    i;
	float	    scale;

	best.cost = FLT_MAX;
	current.axis = 0;
	while (current.axis < 3)
	{
		//bounds_min & bounds_max
		if (node->min[current.axis] == node->max[current.axis])
		{
			current.axis++;
			continue ;
		}
		scale = (node->max[current.axis] - node->min[current.axis]) / 50;
		i = 1;
		while (i < 50)
		{
			current.pos = node->min[current.axis] + i * scale;
			current.cost = evaluate_cost(node, current, scene);
			update_cost(&best, &current);
			i++;
		}
		current.axis++;
	}
	return (best);
}
