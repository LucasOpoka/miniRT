/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:31:32 by atorma            #+#    #+#             */
/*   Updated: 2024/08/28 18:03:24 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../libft/libft.h"
#include <math.h>

void	float_set(float *f, float value);
void	shape_bounds_min_max(float *to_min, float *to_max, t_shape *shape);

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

float	area(float  *min, float *max)
{
	float	extent[3];
	float	area;

	extent[0] = max[0] - min[0];
	extent[1] = max[1] - min[1];
	extent[2] = max[2] - min[2];
	area = extent[0] * extent[1] + extent[1] * extent[2] + extent[2] * extent[0];
	return (area);
}

float	evaluate_cost(t_node *node, t_split current, t_scene *scene)
{
	uint32_t    left_count = 0;
	uint32_t    right_count = 0;
	uint32_t    i = 0;
	float	    min_left[3];
	float	    max_left[3];
	float	    min_right[3];
	float	    max_right[3];

	float_set(min_left, FLT_MAX);
	float_set(min_right, FLT_MAX);
	float_set(max_left, FLT_MIN);
	float_set(max_right, FLT_MIN);
	while (i < node->count)
	{
		t_shape *shape = scene->shapes.arr[scene->bvh_index[node->first_index + i]];
		if (shape->centroid[current.axis] < current.pos)
		{
			shape_bounds_min_max(min_left, max_left, shape);
			left_count++;
		}
		else
		{
			shape_bounds_min_max(min_right, max_right, shape);
			right_count++;
		}
		i++;
	}
	float cost = left_count * area(min_left, max_left) + right_count * area(min_right, max_right);
	if (cost > 0)
	{
		return (cost);
	}
	return (FLT_MAX);
}


void	update_cost(t_split *best, t_split *current)
{
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
