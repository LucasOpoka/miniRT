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
	double	ext[3];
	double	area;

	ext[0] = bounds.max[0] - bounds.min[0];
	ext[1] = bounds.max[1] - bounds.min[1];
	ext[2] = bounds.max[2] - bounds.min[2];
	area = ext[0] * ext[1] + ext[1] * ext[2] + ext[2] * ext[0];
	return (count * area);
}

static int  update_bounds(t_node *node, t_split current,
		t_bounds *bounds, t_scene *scene)
{
	t_obj	    *obj;
	uint32_t    left_count;
	uint32_t    obj_index;
	uint32_t    i;

	left_count = 0;
	i = 0;
	while (i < node->count)
	{
		obj_index = scene->bvh_index[node->first_index + i];
		obj = scene->objs.arr[obj_index];
		if (obj->centroid[current.axis] < current.pos)
		{
			bounds_update(&bounds[0], obj);
			left_count++;
		}
		else
			bounds_update(&bounds[1], obj);
		i++;
	}
	return (left_count);
}

static double	evaluate_cost(t_node *node, t_split current, t_scene *scene)
{
	uint32_t    left_count;
	uint32_t    right_count;
	t_bounds    bounds[2];

	bounds_init(&bounds[0]);
	bounds_init(&bounds[1]);

	left_count = update_bounds(node, current, bounds, scene);
	right_count = node->count - left_count;
	if (!left_count)
		right_count = node->count;
	return (area(bounds[0], left_count) + area(bounds[1], right_count));
}

static void update_cost(t_split *best, t_split *current)
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
