/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:31:32 by atorma            #+#    #+#             */
/*   Updated: 2024/08/28 16:51:24 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../libft/libft.h"
#include <math.h>

void	float_set(float *f, float value);
void	shape_bounds_min_max(float *to_min, float *to_max, t_shape *shape);

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

float	evaluate(t_node *node, int axis, float pos, t_scene *scene)
{
	uint32_t    left_count = 0;
	uint32_t    right_count = 0;
	uint32_t    i = 0;
	float	    cost = 0;
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
		if (shape->centroid[axis] < pos)
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
	cost = left_count * area(min_left, max_left) + right_count * area(min_right, max_right);
	if (cost > 0)
		return cost;
	return (FLT_MAX);
}

float	find_best_split(t_node *node, int *axis, float *split_pos, t_scene *scene)
{
	float	best_cost = FLT_MAX;
	uint32_t    a;
	uint32_t    i;

	a = 0;
	while (a < 3)
	{
		i = 0;
		float bmin = node->min[a];
		float bmax = node->max[a];
		if (bmin == bmax)
		{
			a++;
			continue ;
		}
		float scale = (bmax - bmin) / 64;
		while (i < 64)
		{
			float pos = bmin + i * scale;
			float cost = evaluate(node, a, pos, scene);
			if (cost < best_cost)
			{
				*split_pos = pos;
				*axis = a;
				best_cost = cost;
			}
			i++;
		}
		a++;
	}
	return (best_cost);
}
