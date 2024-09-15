/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:52:11 by atorma            #+#    #+#             */
/*   Updated: 2024/09/15 21:31:28 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <math.h>

void	sphere_bounds(t_bounds *bounds, t_obj *sp);
void	cylinder_bounds(t_bounds *bounds, t_obj *cy);
void	cone_bounds(t_bounds *bounds, t_obj *cone);
void	triangle_bounds(t_bounds *bounds, t_obj *tri);

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

void	bounds_update(t_bounds *bounds, t_obj *obj)
{
	t_bounds	new;

	if (obj->type == t_sphere)
		sphere_bounds(&new, obj);
	else if (obj->type == t_cylinder)
		cylinder_bounds(&new, obj);
	else if (obj->type == t_cone)
		cone_bounds(&new, obj);
	else if (obj->type == t_triangle)
		triangle_bounds(&new, obj);
	bounds_min_max(bounds, &new);
}
