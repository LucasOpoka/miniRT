/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:05:34 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/16 20:11:58 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

// The Raytracer Challenge p.177
void	ft_cylinder_intersection(t_ray ray, t_obj *obj, t_xs *xs)
{
	t_cl_xs	cl;

	cl.a = pow(ray.D.x, 2) + pow(ray.D.z, 2);
	cl.b = 2 * ray.O.x * ray.D.x + 2 * ray.O.z * ray.D.z;
	cl.c = pow(ray.O.x, 2) + pow(ray.O.z, 2) - 1;
	cl.disc = pow(cl.b, 2) - 4 * cl.a * cl.c;
	if (cl.disc >= 0 && cl.a > EPSILON)
	{
		cl.disc = sqrt(cl.disc);
		cl.t[0] = (-cl.b - cl.disc) / (2 * cl.a);
		cl.t[1] = (-cl.b + cl.disc) / (2 * cl.a);
		if (cl.t[0] > cl.t[1])
			ft_swap_doubles(&cl.t[0], &cl.t[1]);
		cl.half_h = 0.5;
		cl.y[0] = ray.O.y + cl.t[0] * ray.D.y;
		if ((-cl.half_h < cl.y[0]) && (cl.y[0] < cl.half_h))
			ft_add_intersection(xs, obj, cl.t[0]);
		cl.y[1] = ray.O.y + cl.t[1] * ray.D.y;
		if ((-cl.half_h < cl.y[1]) && (cl.y[1] < cl.half_h))
			ft_add_intersection(xs, obj, cl.t[1]);
	}
	ft_intersect_caps(ray, obj, xs);
}

void	ft_intersect_caps(t_ray ray, t_obj *obj, t_xs *xs)
{
	double	t;

	if (fabs(ray.D.y) < EPSILON)
		return ;
	t = ((-obj->height / 2) - ray.O.y) / ray.D.y;
	if (ft_check_caps(ray, t, 1))
		ft_add_intersection(xs, obj, t);
	t = ((obj->height / 2) - ray.O.y) / ray.D.y;
	if (ft_check_caps(ray, t, 1))
		ft_add_intersection(xs, obj, t);
}

int	ft_check_caps(t_ray ray, double t, double radius)
{
	double	x;
	double	z;

	x = ray.O.x + ray.D.x * t;
	z = ray.O.z + ray.D.z * t;
	return (pow(x, 2) + pow(z, 2) <= pow(radius, 2));
}

void	ft_swap_doubles(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
