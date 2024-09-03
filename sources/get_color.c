/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:47:05 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/03 18:02:33 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

t_clr	ft_refraction(t_comps *comps, t_light *light, t_scene *scene, int recur_lmt);
t_clr	ft_reflection(t_comps *comps, t_light *light, t_scene *scene, int recur_lmt);
t_clr	ft_light_color(t_ray *ray, t_scene *scene, int recur_lmt, t_xs *xs, t_light *light);


t_clr	ft_final_color(t_ray *ray, t_scene *scene, int recur_lmt, t_xs *xs)
{
	size_t		i;
	t_light		*light;
	t_clr		light_color;
	t_clr		final_color;

	ft_bzero(&final_color, sizeof(t_clr));
	
	i = 0;
	while (i < scene->lights.i)
	{
		light = (t_light *) scene->lights.arr[i++];
		light_color = ft_light_color(ray, scene, recur_lmt, xs, light);
		final_color = ft_clr_add(final_color, light_color);
	}
	return final_color;
}

t_clr	ft_light_color(t_ray *ray, t_scene *scene, int recur_lmt, t_xs *xs, t_light *light)
{
	t_comps			comps;
	t_intrsc		*hit;
	t_clr			surface_color;
	t_clr			reflect_color;
	t_clr			refract_color;
	t_clr			final_color;

	final_color = ft_create_clr(0, 0, 0);
	hit = ft_hit(xs);
	if (!hit)
    	return (final_color);
	ft_prep_comps(&comps, hit, ray, xs);
	surface_color = ft_phong(&comps, scene, light);
	reflect_color = ft_reflection(&comps, light, scene, recur_lmt - 1);
	refract_color = ft_refraction(&comps, light, scene, recur_lmt - 1);
	if (hit->obj->reflective > 0 && hit->obj->transparency > 0)
	{
		reflect_color = ft_clr_scl(reflect_color, comps.schlick);
		refract_color = ft_clr_scl(refract_color, 1 - comps.schlick);
	}
	final_color = ft_clr_add(final_color, surface_color);
	final_color = ft_clr_add(final_color, reflect_color);
	final_color = ft_clr_add(final_color, refract_color);
	return (final_color);
}

t_clr	ft_reflection(t_comps *comps, t_light *light, t_scene *scene, int recur_lmt)
{
	t_ray	reflection_ray;
	t_clr	res;
	

	res = ft_create_clr(0, 0, 0);
	if (comps->obj->reflective == 0 || recur_lmt == 0)
		return (res);
	reflection_ray.O = comps->over_point;
	reflection_ray.D = comps->reflect;
	
	t_xs xs;
	ft_init_xs(&xs);
	ft_get_intrscs(reflection_ray, scene, &xs);	
	
	res = ft_light_color(&reflection_ray, scene, recur_lmt, &xs, light);

	ft_free_xs(&xs);

	res = ft_clr_scl(res, comps->obj->reflective);
	return (res);
}

t_clr	ft_refraction(t_comps *comps, t_light *light, t_scene *scene, int recur_lmt)
{
	t_ray	refraction_ray;
	t_clr	res;
	double	n_ratio;

	res = ft_create_clr(0, 0, 0);
	if (comps->obj->transparency == 0 || recur_lmt == 0)
		return (res);
	n_ratio = comps->n1 / comps->n2;
	
	double cos_i = ft_vct_dot(&comps->eye, &comps->normal);
	double sin2_t = pow(n_ratio, 2) * (1 - pow(cos_i, 2));
	if (sin2_t > 1)
		return (res);
	double cos_t = sqrt(1 - sin2_t);

	t_vct tmp1 = ft_vct_sclr_mult(&comps->normal, n_ratio * cos_i - cos_t);
	t_vct tmp2 = ft_vct_sclr_mult(&comps->eye, n_ratio);
	refraction_ray.D = ft_vct_sub(&tmp1, &tmp2);

	refraction_ray.O = comps->under_point;
	
	t_xs xs;
	ft_init_xs(&xs);
	ft_get_intrscs(refraction_ray, scene, &xs);	
	
	res = ft_light_color(&refraction_ray, scene, recur_lmt, &xs, light);
	
	res = ft_clr_scl(res, comps->obj->transparency);

	ft_free_xs(&xs);

	return (res);
}
