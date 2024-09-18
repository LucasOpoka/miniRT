/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:05:34 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/18 17:52:55 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/miniRT.h"

void	ft_cone_intersection(t_ray r, t_obj *obj, t_xs *xs)
{
	t_cl_xs	cl;

	cl.a = pow(r.D.x, 2) - pow(r.D.y, 2) + pow(r.D.z, 2);
	cl.b = 2 * r.O.x * r.D.x - 2 * r.O.y * r.D.y + 2 * r.O.z * r.D.z;
	cl.c = pow(r.O.x, 2) - pow(r.O.y, 2) + pow(r.O.z, 2);
	cl.disc = pow(cl.b, 2) - 4 * cl.a * cl.c;
	if (cl.disc >= 0 && cl.a > EPSILON)
	{
		cl.disc = sqrt(cl.disc);
		cl.t[0] = (-cl.b - cl.disc) / (2 * cl.a);
		cl.t[1] = (-cl.b + cl.disc) / (2 * cl.a);
		if (cl.t[0] > cl.t[1])
			ft_swap_doubles(&cl.t[0], &cl.t[1]);
		cl.y[0] = r.O.y + cl.t[0] * r.D.y;
		if ((0 < cl.y[0]) && (cl.y[0] < 1))
			ft_add_intersection(xs, obj, cl.t[0]);
		cl.y[1] = r.O.y + cl.t[1] * r.D.y;
		if ((0 < cl.y[1]) && (cl.y[1] < 1))
			ft_add_intersection(xs, obj, cl.t[1]);
	}
	ft_intersect_cone_caps(r, obj, xs);
}

void	ft_intersect_cone_caps(t_ray ray, t_obj *obj, t_xs *xs)
{
	double	t;

	if (fabs(ray.D.y) < EPSILON)
		return ;
	t = (1 - ray.O.y) / ray.D.y;
	if (ft_check_caps(ray, t, 1))
		ft_add_intersection(xs, obj, t);
	t = -ray.O.y / ray.D.y;
	if (ft_check_caps(ray, t, 0))
		ft_add_intersection(xs, obj, t);
}
