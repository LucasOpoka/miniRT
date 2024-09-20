/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:47:05 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/20 16:23:01 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

t_clr	ft_final_color(t_ray *ray, t_scene *scene, int recur_lmt, t_xs *xs)
{
	size_t		i;
	t_clr_recur	rec;
	t_clr		light_color;
	t_clr		final_color;

	rec.ray = *ray;
	rec.scene = scene;
	rec.xs = xs;
	rec.recur_lmt = recur_lmt;
	rec.xs->i = 0;
	if (scene->bvh.nodes_used < 3)
		ft_get_intrscs(rec.ray, rec.scene, rec.xs);
	else
		bvh_intersect(rec.ray, rec.scene, rec.xs);
	rec.comps = ft_prep_comps(&rec.ray, rec.xs);
	final_color = ft_create_clr(0, 0, 0);
	i = 0;
	while (i < scene->lights.i)
	{
		rec.light = (t_light *) scene->lights.arr[i++];
		light_color = ft_light_color(rec);
		final_color = ft_clr_add(final_color, light_color);
	}
	return (final_color);
}

t_clr	ft_light_color(t_clr_recur rec)
{
	t_clr	surface_color;
	t_clr	reflect_color;
	t_clr	refract_color;
	t_clr	final_color;

	final_color = ft_create_clr(0, 0, 0);
	if (!rec.comps.hit)
		return (final_color);
	surface_color = ft_phong(&rec);
	rec.recur_lmt--;
	reflect_color = ft_reflection(rec);
	refract_color = ft_refraction(rec);
	if (rec.comps.obj->reflective > 0 && rec.comps.obj->transparency > 0)
	{
		reflect_color = ft_clr_scl(reflect_color, rec.comps.schlick);
		refract_color = ft_clr_scl(refract_color, 1 - rec.comps.schlick);
	}
	final_color = ft_clr_add(final_color, surface_color);
	final_color = ft_clr_add(final_color, reflect_color);
	final_color = ft_clr_add(final_color, refract_color);
	return (final_color);
}

t_clr	ft_reflection(t_clr_recur rec)
{
	t_clr	res;
	double	reflective;

	res = ft_create_clr(0, 0, 0);
	if (rec.comps.obj->reflective == 0 || rec.recur_lmt < 0)
		return (res);
	reflective = rec.comps.obj->reflective;
	rec.ray.o = rec.comps.over_point;
	rec.ray.d = rec.comps.reflect;
	rec.xs->i = 0;
	if (rec.scene->bvh.nodes_used < 3)
		ft_get_intrscs(rec.ray, rec.scene, rec.xs);
	else
		bvh_intersect(rec.ray, rec.scene, rec.xs);
	rec.comps = ft_prep_comps(&rec.ray, rec.xs);
	res = ft_light_color(rec);
	res = ft_clr_scl(res, reflective);
	return (res);
}

t_clr	ft_refraction(t_clr_recur rec)
{
	t_refraction	rf;

	rf.res = ft_create_clr(0, 0, 0);
	if (rec.comps.obj->transparency == 0 || rec.recur_lmt < 0)
		return (rf.res);
	rf.transparency = rec.comps.obj->transparency;
	rf.n_ratio = rec.comps.n1 / rec.comps.n2;
	rf.cos_i = ft_vct_dot(&rec.comps.eye, &rec.comps.normal);
	rf.sin2_t = pow(rf.n_ratio, 2) * (1 - pow(rf.cos_i, 2));
	if (rf.sin2_t > 1)
		return (rf.res);
	rf.cos_t = sqrt(1 - rf.sin2_t);
	rf.v1 = ft_vct_x_sclr(&rec.comps.normal, rf.n_ratio * rf.cos_i - rf.cos_t);
	rf.v2 = ft_vct_x_sclr(&rec.comps.eye, rf.n_ratio);
	rec.ray.d = ft_vct_sub(&rf.v1, &rf.v2);
	rec.ray.o = rec.comps.under_point;
	rec.xs->i = 0;
	if (rec.scene->bvh.nodes_used < 3)
		ft_get_intrscs(rec.ray, rec.scene, rec.xs);
	else
		bvh_intersect(rec.ray, rec.scene, rec.xs);
	rec.comps = ft_prep_comps(&rec.ray, rec.xs);
	rf.res = ft_light_color(rec);
	rf.res = ft_clr_scl(rf.res, rf.transparency);
	return (rf.res);
}
