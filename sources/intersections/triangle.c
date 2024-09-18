/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:05:34 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/18 17:53:16 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/miniRT.h"

void	ft_triangle_intersection(t_ray ray, t_obj *obj, t_xs *xs)
{
	t_tri_xs	tri;

	ft_vct_cross_prod(&tri.dir_cros_e2, &ray.D, &obj->e2);
	tri.det = ft_vct_dot(&obj->e1, &tri.dir_cros_e2);
	if (fabs(tri.det) < EPSILON)
		return ;
	tri.f = 1.0 / tri.det;
	tri.p1_to_origin = ft_vct_sub(&ray.O, &obj->p1);
	tri.u = tri.f * ft_vct_dot(&tri.p1_to_origin, &tri.dir_cros_e2);
	if (tri.u < 0 || 1 < tri.u)
		return ;
	ft_vct_cross_prod(&tri.origin_cross_e1, &tri.p1_to_origin, &obj->e1);
	tri.v = tri.f * ft_vct_dot(&ray.D, &tri.origin_cross_e1);
	if (tri.v < 0 || 1 < (tri.u + tri.v))
		return ;
	tri.t = tri.f * ft_vct_dot(&obj->e2, &tri.origin_cross_e1);
	ft_add_intersection(xs, obj, tri.t);
}
