/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:09:25 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/03 18:31:53 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

t_clr	ft_phong(t_comps *comps, t_scene *scene, t_light *light)
{
	t_phong	ph;

	ph.result = ft_ambient(&scene->ambient, &comps->color);
	ph.effective = ft_clrs_mult(comps->obj->color, light->color);
	ph.light_vct = ft_vct_sub(&light->pos, &comps->over_point);
	ft_vct_norm(&ph.light_vct);
	comps->normal.w = 0;
	ph.lght_dot_norm = ft_vct_dot(&ph.light_vct, &comps->normal);
	if (ph.lght_dot_norm < 0 || ft_shadow(scene, light, &comps->over_point))
		return (ph.result);
	ph.diffuse = ft_diffuse(&ph, comps, light);
	ph.specular = ft_specular(&ph, comps, light);
	ph.result = ft_clr_add(ph.result, ph.diffuse);
	ph.result = ft_clr_add(ph.result, ph.specular);
	return (ph.result);
}

t_clr	ft_ambient(t_ambient *ambient, t_clr *obj_color)
{
	t_clr	temp;
	t_clr	res;

	temp = ft_clr_scl(*obj_color, ambient->intensity);
	res = ft_clrs_mult(temp, ambient->color);
	return (res);
}

t_clr	ft_diffuse(t_phong *ph, t_comps *comps, t_light *light)
{
	double	scl;

	scl = ph->lght_dot_norm * comps->obj->diffuse * light->intensity;
	return (ft_clr_scl(ph->effective, scl));
}

t_clr	ft_specular(t_phong *ph, t_comps *comps, t_light *light)
{
	t_clr	res;
	t_vct	neg_light_vct;
	t_vct	reflect_vct;
	double	refl_dot_eye;
	double	scl;

	neg_light_vct = ft_vct_neg(&ph->light_vct);
	reflect_vct = ft_reflect(&neg_light_vct, &comps->normal);
	refl_dot_eye = ft_vct_dot(&reflect_vct, &comps->eye);
	if (refl_dot_eye < 0)
		res = ft_create_clr(0, 0, 0);
	else
	{
		scl = light->intensity * comps->obj->specular;
		scl *= pow(refl_dot_eye, comps->obj->shininess);
		res = ft_clr_scl(light->color, scl);
	}
	return (res);
}

int	ft_shadow(t_scene *scene, t_light *light, t_vct *over_point)
{
	t_ray		point_to_light;
	float		distance;
	int			res;
	t_xs		xs;
	t_intrsc	*hit;

	point_to_light.D = ft_vct_sub(&light->pos, over_point);
	distance = ft_vct_len(&point_to_light.D);
	ft_vct_norm(&point_to_light.D);
	point_to_light.O = *over_point;
	ft_init_xs(&xs);
	ft_get_intrscs(point_to_light, scene, &xs);
	hit = ft_hit(&xs);
	res = 0;
	if (hit && hit->t < distance)
		res = 1;
	ft_free_xs(&xs);
	return (res);
}
