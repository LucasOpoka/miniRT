/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_comps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:28:57 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/26 16:41:38 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

// prepare_computations - The Ray Tracer Challenge p.76 p.93
void	ft_prepare_computations(t_comps *comps, t_intersection *closest, const t_ray *ray)
{
	comps->t = closest->t;
	comps->shape = closest->shape;
	comps->point = ft_ray_point(ray, comps->t); 
	comps->eye = ft_vct_neg(&ray->D);
	comps->eye.w = 0;
	comps->normal = ft_shape_normal(comps->shape, &comps->point);
	comps->inside = 0;
	if (ft_vct_dot(&comps->normal, &comps->eye) < 0)
	{
		comps->inside = 1;
		comps->normal = ft_vct_neg(&comps->normal);
	}
	comps->reflect = ft_reflect(&ray->D, &comps->normal);
	comps->over_point = ft_over_point(&comps->point, &comps->normal);
}

// position - The Ray Tracer Challenge p.58
t_vct	ft_ray_point(const t_ray *ray, float t)
{
	t_vct	position;

	position.x = ray->O.x + ray->D.x * t;
	position.y = ray->O.y + ray->D.y * t;
	position.z = ray->O.z + ray->D.z * t;
	position.w = 1;
	return (position);
}

// reflect - The Ray Tracer Challenge p.83
t_vct	ft_reflect(const t_vct *in, const t_vct *normal)
{
	t_vct	res;

	res = ft_vct_sclr_mult(normal, 2 * ft_vct_dot(in, normal));
	res = ft_vct_sub(in, &res);
	return (res);
}

// over_point - The Ray Tracer Challenge p.115
t_vct	ft_over_point(const t_vct *point, const t_vct *normal)
{
	t_vct	res;

	res = ft_vct_sclr_mult(normal, EPSILON);
	res = ft_vct_add(point, &res);
	return (res);
}

