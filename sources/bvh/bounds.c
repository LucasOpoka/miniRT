/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:52:11 by atorma            #+#    #+#             */
/*   Updated: 2024/09/05 17:48:33 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <math.h>

/*
* http://raytracerchallenge.com/bonus/bounding-boxes.html
*/

void	bounds_min_max(t_bounds *to, t_bounds *new)
{
	to->min[0] = fmin(to->min[0], new->min[0]);
	to->min[1] = fmin(to->min[1], new->min[1]);
	to->min[2] = fmin(to->min[2], new->min[2]);
	to->max[0] = fmax(to->max[0], new->max[0]);
	to->max[1] = fmax(to->max[1], new->max[1]);
	to->max[2] = fmax(to->max[2], new->max[2]);
}

void	sphere_bounds(t_bounds *bounds, t_obj *sp)
{
	const t_vct	scale = sp->scale;
	const double	radius = sp->radius;

	bounds->min[0] = scale.x * -radius + sp->pos.x;
	bounds->min[1] = scale.y * -radius + sp->pos.y;
	bounds->min[2] = scale.z * -radius + sp->pos.z;

	bounds->max[0] = scale.x * radius + sp->pos.x;
	bounds->max[1] = scale.y * radius + sp->pos.y;
	bounds->max[2] = scale.z * radius + sp->pos.z;
}

void	cylinder_bounds(t_bounds *bounds, t_obj *cy)
{
	const t_vct	scale = cy->scale;
	const double	radius = cy->radius * 2;
	const double	height = cy->height;

	bounds->min[0] = scale.x * -radius + cy->pos.x;
	bounds->min[1] = scale.y * -radius + cy->pos.y;
	bounds->min[2] = scale.z * -height + cy->pos.z;

	bounds->max[0] = scale.x * radius + cy->pos.x;
	bounds->max[1] = scale.y * radius + cy->pos.y;
	bounds->max[2] = scale.z * height + cy->pos.z;
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
