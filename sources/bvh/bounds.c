/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:52:11 by atorma            #+#    #+#             */
/*   Updated: 2024/08/28 16:52:13 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <math.h>

void	node_min_max(float *to_min, float *to_max, float *min, float *max);

void	sphere_bounds(float *min, float *max, t_shape *sphere)
{
	t_vct	pos = sphere->position;
	t_vct	scale = sphere->scale;
	float	radius = sphere->radius;

	min[0] = scale.x * -radius + pos.x;
	min[1] = scale.y * -radius + pos.y;
	min[2] = scale.z * -radius + pos.z;

	max[0] = scale.x * radius + pos.x;
	max[1] = scale.y * radius + pos.y;
	max[2] = scale.z * radius + pos.z;
}

void	cylinder_bounds(float *min, float *max, t_shape *cylinder)
{
	t_vct scale = cylinder->scale;
	t_vct pos = cylinder->position;
	float	radius = 1;

	min[0] = scale.x * -radius + pos.x;
	max[0] = scale.x * radius + pos.x;
	min[1] = scale.y * -radius + pos.y;
	max[1] = scale.y * radius + pos.y;
	min[2] = scale.z * -(cylinder->height / 2.0) + pos.z;
	max[2] = scale.z * (cylinder->height / 2.0) + pos.z;
}


void	shape_bounds_update(t_node *node, t_shape *shape)
{
	float	min[3];
	float	max[3];

	if (shape->type == t_sphere)
		sphere_bounds(min, max, shape);
	else if (shape->type == t_cylinder)
		cylinder_bounds(min, max, shape);
	node_min_max(node->min, node->max, min, max);
}

void	shape_bounds_min_max(float *to_min, float *to_max, t_shape *shape)
{
	float	min[3];
	float	max[3];

	if (shape->type == t_sphere)
		sphere_bounds(min, max, shape);
	else if (shape->type == t_cylinder)
		cylinder_bounds(min, max, shape);
	node_min_max(to_min, to_max, min, max);
}