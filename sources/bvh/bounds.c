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

void	node_min_max(double *to_min, double *to_max, double *min, double *max);

void	sphere_bounds(double *min, double *max, t_obj *sphere)
{
	t_vct	pos = sphere->pos;
	t_vct	scale = sphere->scale;
	double	radius = sphere->radius;

	min[0] = scale.x * -radius + pos.x;
	min[1] = scale.y * -radius + pos.y;
	min[2] = scale.z * -radius + pos.z;

	max[0] = scale.x * radius + pos.x;
	max[1] = scale.y * radius + pos.y;
	max[2] = scale.z * radius + pos.z;
}

void	cylinder_bounds(double *min, double *max, t_obj *cylinder)
{
	t_vct scale = cylinder->scale;
	t_vct pos = cylinder->pos;
	double	radius = 1;

	min[0] = scale.x * -radius + pos.x;
	max[0] = scale.x * radius + pos.x;
	min[1] = scale.y * -radius + pos.y;
	max[1] = scale.y * radius + pos.y;
	min[2] = scale.z * -(cylinder->height / 2.0) + pos.z;
	max[2] = scale.z * (cylinder->height / 2.0) + pos.z;
}


void	obj_bounds_update(t_node *node, t_obj *obj)
{
	double	min[3];
	double	max[3];

	if (obj->type == t_sphere)
		sphere_bounds(min, max, obj);
	else if (obj->type == t_cylinder)
		cylinder_bounds(min, max, obj);
	node_min_max(node->min, node->max, min, max);
}

void	obj_bounds_min_max(double *to_min, double *to_max, t_obj *obj)
{
	double	min[3];
	double	max[3];

	if (obj->type == t_sphere)
		sphere_bounds(min, max, obj);
	else if (obj->type == t_cylinder)
		cylinder_bounds(min, max, obj);
	node_min_max(to_min, to_max, min, max);
}
