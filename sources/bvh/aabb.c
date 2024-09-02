/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:52:02 by atorma            #+#    #+#             */
/*   Updated: 2024/08/28 16:52:04 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <math.h>

/*
if tmax < 0, ray is intersecting AABB, but whole AABB is behind camera
if tmin > tmax, ray doesn't intersect AABB
*/

double	aabb_raycast(t_ray ray, t_bounds bounds)
{
	double t1 = (bounds.min[0] - ray.O.x) * ray.rd.x;
	double t2 = (bounds.max[0] - ray.O.x) * ray.rd.x;
	double t3 = (bounds.min[1] - ray.O.y) * ray.rd.y;
	double t4  = (bounds.max[1] - ray.O.y) * ray.rd.y;
	double t5 = (bounds.min[2] - ray.O.z) * ray.rd.z;
	double t6 = (bounds.max[2] - ray.O.z) * ray.rd.z;

	double tmin = fmax(fmaxf(fmin(t1, t2), fmin(t3, t4)), fmin(t5, t6));
	double tmax = fmin(fminf(fmax(t1, t2), fmax(t3, t4)), fmax(t5, t6));

	if (tmax < 0 || tmin > tmax)
		return (DBL_MAX);
	return (0);
}
