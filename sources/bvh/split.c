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

void	bounds_init(t_bounds *bounds);
void	bounds_update(t_bounds *bounds, t_obj *obj);

static double	area(t_bounds bounds, uint32_t	count)
{
	double	extent[3];
	double	area;

	extent[0] = bounds.max[0] - bounds.min[0];
	extent[1] = bounds.max[1] - bounds.min[1];
	extent[2] = bounds.max[2] - bounds.min[2];
	area = extent[0] * extent[1] + extent[1] * extent[2] + extent[2] * extent[0];
	return (count * area);
}


double	evaluate_cost(t_node *node, t_split current, t_scene *scene)
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
			bounds_update(&left, obj);
			left_count++;
		}
		else
		{
			bounds_update(&right, obj);
			right_count++;
		}
		i++;
	}
	return (area(left, left_count) + area(right, right_count));
}


void	update_cost(t_split *best, t_split *current)
{
	if (current->cost > 0 && current->cost < best->cost)
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
	double	    scale;

	best.cost = DBL_MAX;
	current.axis = 0;
	while (current.axis < 3)
	{
		//bounds_min & bounds_max
		if (node->bounds.min[current.axis] == node->bounds.max[current.axis])
		{
			current.axis++;
			continue ;
		}
		scale = (node->bounds.max[current.axis] - node->bounds.min[current.axis]) / 50;
		i = 1;
		while (i < 50)
		{
			current.pos = node->bounds.min[current.axis] + i * scale;
			current.cost = evaluate_cost(node, current, scene);
			update_cost(&best, &current);
			i++;
		}
		current.axis++;
	}
	return (best);
}
