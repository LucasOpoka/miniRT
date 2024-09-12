/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_and_bump.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:08:11 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/12 12:13:20 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/miniRT.h"

void	ft_get_txtr(t_comps *comps, t_obj *obj, double *uv);
void	ft_get_bump(t_comps *comps, t_obj *obj, t_vct p, double *uv);

void	ft_texture_and_bump(t_comps *comps, t_obj *obj, t_vct obj_point)
{
	double	uv[2];

	ft_spherical_map(uv, &obj_point);
	uv[1] = 1 - uv[1];
	if (obj->txtr.colors)
		ft_get_txtr(comps, obj, uv);
	if (obj->bump.colors)
		ft_get_bump(comps, obj, obj_point, uv);
}

double	ft_grscl(t_clr clr)
{
	return (0.3 * clr.r + 0.6 * clr.g + 0.1 * clr.b);
}

void	ft_get_bump(t_comps *comps, t_obj *obj, t_vct p, double *uv)
{
	t_txtr_bump	s;

	s.x = round(uv[0] * (obj->bump.width - 1));
	s.y = round(uv[1] * (obj->bump.height - 1));
	s.theta = atan2(p.z, p.x);
	s.radius = ft_vct_len(&p);
	s.phi = acos(p.y / s.radius);
	s.obj_norm = p;
	s.obj_norm.w = 0;
	s.tan = ft_create_vct(2 * M_PI * p.z, 0, -2 * M_PI * p.x);
	s.bitan = ft_create_vct(M_PI * p.y * cos(s.theta),
			-s.radius * M_PI * sin(s.phi), M_PI * p.y * sin(s.theta));
	ft_vct_norm(&s.tan);
	ft_vct_norm(&s.bitan);
	s.h1 = ft_grscl(obj->bump.colors[(s.y + 1) % obj->bump.height][s.x]) * 30;
	s.h_uv = ft_grscl(obj->bump.colors[s.y][s.x]) * 30;
	s.h2 = ft_grscl(obj->bump.colors[s.y][(s.x + 1) % obj->bump.width]) * 30;
	s.q_u = ft_vct_x_sclr(&s.obj_norm, s.h1 - s.h_uv);
	s.q_v = ft_vct_x_sclr(&s.obj_norm, s.h2 - s.h_uv);
	s.q_u = ft_vct_add(&s.tan, &s.q_u);
	s.q_v = ft_vct_add(&s.bitan, &s.q_v);
	ft_vct_cross_prod(&s.obj_norm, &s.q_v, &s.q_u);
	ft_vct_x_mtrx(&comps->normal, &obj->normal_to_world, &s.obj_norm);
	comps->normal.w = 0;
	ft_vct_norm(&comps->normal);
}

void	ft_get_txtr(t_comps *comps, t_obj *obj, double *uv)
{
	t_txtr_bump	s;

	s.x = round(uv[0] * (obj->txtr.width - 1));
	s.y = round(uv[1] * (obj->txtr.height - 1));
	comps->color = obj->txtr.colors[s.y][s.x];
}
