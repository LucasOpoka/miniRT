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
	t_aabb_time	t;
	double		tmin;
	double		tmax;

	t.t1 = (bounds.min[0] - ray.O.x) * ray.rd.x;
	t.t2 = (bounds.max[0] - ray.O.x) * ray.rd.x;
	t.t3 = (bounds.min[1] - ray.O.y) * ray.rd.y;
	t.t4 = (bounds.max[1] - ray.O.y) * ray.rd.y;
	t.t5 = (bounds.min[2] - ray.O.z) * ray.rd.z;
	t.t6 = (bounds.max[2] - ray.O.z) * ray.rd.z;
	tmin = fmax(fmax(fmin(t.t1, t.t2), fmin(t.t3, t.t4)), fmin(t.t5, t.t6));
	tmax = fmin(fmin(fmax(t.t1, t.t2), fmax(t.t3, t.t4)), fmax(t.t5, t.t6));
	if (tmax < 0 || tmin > tmax)
		return (DBL_MAX);
	return (0);
}
