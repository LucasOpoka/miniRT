/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:09:25 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/20 17:08:27 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/miniRT.h"

t_clr	ft_phong(t_clr_recur *rec)
{
	t_phong	ph;

	ph.result = ft_ambient(rec);
	ph.effective = ft_clr_x_clr(rec->comps.obj->color, rec->light->color);
	ph.light_vct = ft_vct_sub(&rec->light->pos, &rec->comps.over_point);
	ft_vct_norm(&ph.light_vct);
	rec->comps.normal.w = 0;
	ph.lght_dot_norm = ft_vct_dot(&ph.light_vct, &rec->comps.normal);
	if (ph.lght_dot_norm < 0 || ft_shadow(rec))
		return (ph.result);
	ph.diffuse = ft_diffuse(&ph, rec);
	ph.specular = ft_specular(&ph, rec);
	ph.result = ft_clr_add(ph.result, ph.diffuse);
	ph.result = ft_clr_add(ph.result, ph.specular);
	return (ph.result);
}

t_clr	ft_ambient(t_clr_recur *rec)
{
	t_clr	temp;
	t_clr	res;

	temp = ft_clr_scl(rec->comps.color, rec->scene->ambient.intensity);
	res = ft_clr_x_clr(temp, rec->scene->ambient.color);
	return (res);
}

t_clr	ft_diffuse(t_phong *ph, t_clr_recur *rec)
{
	double	scl;

	scl = ph->lght_dot_norm * rec->comps.obj->diffuse * rec->light->intensity;
	return (ft_clr_scl(ph->effective, scl));
}

t_clr	ft_specular(t_phong *ph, t_clr_recur *rec)
{
	t_clr	res;
	t_vct	neg_light_vct;
	t_vct	reflect_vct;
	double	refl_dot_eye;
	double	scl;

	neg_light_vct = ft_vct_neg(&ph->light_vct);
	reflect_vct = ft_reflect(&neg_light_vct, &rec->comps.normal);
	refl_dot_eye = ft_vct_dot(&reflect_vct, &rec->comps.eye);
	if (refl_dot_eye < 0)
		res = ft_create_clr(0, 0, 0);
	else
	{
		scl = rec->light->intensity * rec->comps.obj->specular;
		scl *= pow(refl_dot_eye, rec->comps.obj->shininess);
		res = ft_clr_scl(rec->light->color, scl);
	}
	return (res);
}

int	ft_shadow(t_clr_recur *rec)
{
	t_ray		point_to_light;
	float		distance;
	int			res;
	t_intrsc	*hit;

	point_to_light.d = ft_vct_sub(&rec->light->pos, &rec->comps.over_point);
	distance = ft_vct_len(&point_to_light.d);
	ft_vct_norm(&point_to_light.d);
	point_to_light.o = rec->comps.over_point;
	rec->xs->i = 0;
	if (rec->scene->bvh.nodes_used < 3)
		ft_get_intrscs(point_to_light, rec->scene, rec->xs);
	else
		bvh_intersect(point_to_light, rec->scene, rec->xs);
	hit = ft_hit(rec->xs);
	res = 0;
	if (hit && hit->t < distance)
		res = 1;
	return (res);
}
