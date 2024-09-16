/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:07:43 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/16 12:43:22 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/miniRT.h"

void	ft_get_uv(double *uv, t_vct *p, t_obj *obj)
{
	if (obj->type == t_sphere)
		ft_spherical_map(uv, p);
	if (obj->type == t_plane)
		ft_planar_map(uv, p);
	if (obj->type == t_cylinder)
		ft_cylindrical_map(uv, p);
	if (obj->type == t_cone)
		ft_conical_map(uv, p);
	if (obj->type == t_triangle)
		ft_triangle_map(uv, p);
}

void	ft_spherical_map(double *uv, t_vct *p)
{
	double	theta;
	double	phi;
	double	radius;

	theta = atan2(p->x, p->z);
	radius = ft_vct_len(p);
	phi = acos(p->y / radius);
	uv[0] = 1 - ((theta / (2 * M_PI)) + 0.5);
	uv[1] = 1 - phi / M_PI;
}

void	ft_planar_map(double *uv, t_vct *p)
{
	uv[0] = (float) fmod(p->x, 1.0);
	uv[1] = (float) fmod(p->z, 1.0);
}

void	ft_cylindrical_map(double *uv, t_vct *p)
{
	double	theta;

	theta = atan2(p->x, p->z);
	uv[0] = 1 - ((theta / (2 * M_PI)) + 0.5);
	uv[1] = (float) fmod(p->y, 1.0);
}
