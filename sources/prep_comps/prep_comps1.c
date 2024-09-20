/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_comps1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:28:57 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/20 16:52:28 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/miniRT.h"

// prepare computations - The Ray Tracer Challenge p.76 p.93
t_comps	ft_prep_comps(t_ray *ray, t_xs *xs)
{
	t_comps	comps;

	ft_bzero(&comps, sizeof(t_comps));
	comps.hit = ft_hit(xs);
	if (!comps.hit)
		return (comps);
	comps.t = comps.hit->t;
	comps.obj = comps.hit->obj;
	comps.point = ft_ray_point(ray, comps.t);
	comps.eye = ft_vct_neg(&ray->d);
	comps.eye.w = 0;
	ft_get_obj_normal_and_color(&comps);
	comps.inside = 0;
	if (ft_vct_dot(&comps.normal, &comps.eye) < 0)
	{
		comps.inside = 1;
		comps.normal = ft_vct_neg(&comps.normal);
	}
	comps.reflect = ft_reflect(&ray->d, &comps.normal);
	comps.over_point = ft_over_point(&comps.point, &comps.normal);
	comps.under_point = ft_under_point(&comps.point, &comps.normal);
	ft_get_refr_ind(&comps, xs, comps.hit);
	ft_get_schlick(&comps);
	return (comps);
}

// pos - The Ray Tracer Challenge p.58
t_vct	ft_ray_point(const t_ray *ray, double t)
{
	t_vct	point;

	point.x = ray->o.x + ray->d.x * t;
	point.y = ray->o.y + ray->d.y * t;
	point.z = ray->o.z + ray->d.z * t;
	point.w = 1;
	return (point);
}

// reflect - The Ray Tracer Challenge p.83
t_vct	ft_reflect(const t_vct *in, const t_vct *normal)
{
	t_vct	res;

	res = ft_vct_x_sclr(normal, 2 * ft_vct_dot(in, normal));
	res = ft_vct_sub(in, &res);
	return (res);
}

// over_point - The Ray Tracer Challenge p.115
t_vct	ft_over_point(const t_vct *point, const t_vct *normal)
{
	t_vct	res;

	res = ft_vct_x_sclr(normal, EPSILON);
	res = ft_vct_add(point, &res);
	return (res);
}

// under_point - The Ray Tracer Challenge p.155
t_vct	ft_under_point(const t_vct *point, const t_vct *normal)
{
	t_vct	res;

	res = ft_vct_x_sclr(normal, EPSILON);
	res = ft_vct_sub(point, &res);
	return (res);
}
