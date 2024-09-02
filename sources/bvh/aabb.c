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

double aabb_raycast(t_ray ray, double bmin[3], double bmax[3])
{
	/*
    t_vct   rd;
    rd.x = 1.0 / ray.D.x;
    rd.y = 1.0 / ray.D.y;
    rd.z = 1.0 / ray.D.z;
    */
    double t1 = (bmin[0] - ray.O.x) * ray.rd.x;
    double t2 = (bmax[0] - ray.O.x) * ray.rd.x;
    double t3 = (bmin[1] - ray.O.y) * ray.rd.y;
    double t4  = (bmax[1] - ray.O.y) * ray.rd.y;
    double t5 = (bmin[2] - ray.O.z) * ray.rd.z;
    double t6 = (bmax[2] - ray.O.z) * ray.rd.z;

    double tmin = fmax(fmaxf(fmin(t1, t2), fmin(t3, t4)), fmin(t5, t6));
    double tmax = fmin(fminf(fmax(t1, t2), fmax(t3, t4)), fmax(t5, t6));

    // if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
    if (tmax < 0)
	return (DBL_MAX);
    // if tmin > tmax, ray doesn't intersect AABB
    if (tmin > tmax)
	return (DBL_MAX);
    return (0);
    //return (tmin < tmax);
}
