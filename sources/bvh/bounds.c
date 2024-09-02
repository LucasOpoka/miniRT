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

void	bounds_min_max(t_bounds *to, t_bounds *new)
{
	to->min[0] = fmin(to->min[0], new->min[0]);
	to->min[1] = fmin(to->min[1], new->min[1]);
	to->min[2] = fmin(to->min[2], new->min[2]);

	to->max[0] = fmax(to->max[0], new->max[0]);
	to->max[1] = fmax(to->max[1], new->max[1]);
	to->max[2] = fmax(to->max[2], new->max[2]);
}

void	sphere_bounds(t_bounds *bounds, t_obj *sphere)
{
	t_vct	pos = sphere->pos;
	t_vct	scale = sphere->scale;
	double	radius = sphere->radius;

	bounds->min[0] = scale.x * -radius + pos.x;
	bounds->min[1] = scale.y * -radius + pos.y;
	bounds->min[2] = scale.z * -radius + pos.z;

	bounds->max[0] = scale.x * radius + pos.x;
	bounds->max[1] = scale.y * radius + pos.y;
	bounds->max[2] = scale.z * radius + pos.z;
}

void	cylinder_bounds(t_bounds *bounds, t_obj *cylinder)
{
	t_vct scale = cylinder->scale;
	t_vct pos = cylinder->pos;
	double	radius = 1;

	bounds->min[0] = scale.x * -radius + pos.x;
	bounds->max[0] = scale.x * radius + pos.x;
	bounds->min[1] = scale.y * -radius + pos.y;
	bounds->max[1] = scale.y * radius + pos.y;
	bounds->min[2] = scale.z * -(cylinder->height / 2.0) + pos.z;
	bounds->max[2] = scale.z * (cylinder->height / 2.0) + pos.z;
}

void	bounds_update(t_bounds *bounds, t_obj *obj)
{
	t_bounds    new;

	if (obj->type == t_sphere)
		sphere_bounds(&new, obj);
	else if (obj->type == t_cylinder)
		cylinder_bounds(&new, obj);
	bounds_min_max(bounds, &new);
}
