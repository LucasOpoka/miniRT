/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:47:05 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/01 18:57:01 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

t_clr	ft_refraction(t_comps *comps, t_light *light, t_scene *scene, int recursion_depth);
t_clr	ft_reflection(t_comps *comps, t_light *light, t_scene *scene, int recursion_depth);
t_clr	ft_get_color2(const t_ray *ray, t_scene *scene, int recursion_depth, t_xs *xs, t_light *light);

t_clr	ft_get_color(const t_ray *ray, t_scene *scene, int recursion_depth, t_xs *xs)
{
	t_comps			comps;
	t_intersection	*closest;
	t_clr			ambient;
	t_clr			surface_color;
	t_clr			reflect_color;
	t_clr			refract_color;
	size_t			i;
	t_light			*light;
	t_clr			final_color;

	ft_bzero(&final_color, sizeof(t_clr));

	closest = ft_closest_intersection(xs);
	if (!closest)
    	return (ft_create_clr(0, 0, 0));

	ft_prep_comps(&comps, closest, ray, xs);
	
	ambient = ft_get_ambient(&scene->ambient, &comps.color);

	i = 0;
	while (i < scene->lights.i)
	{
		light = (t_light *) scene->lights.arr[i++];
		surface_color = ft_lighting(&comps, scene, light, &ambient);
		reflect_color = ft_reflection(&comps, light, scene, recursion_depth);
		refract_color = ft_refraction(&comps, light, scene, recursion_depth);
		if (closest->obj->reflective > 0 && closest->obj->transparency > 0)
		{
			reflect_color = ft_clr_sclr_mult(reflect_color, comps.schlick);
			refract_color = ft_clr_sclr_mult(refract_color, 1 - comps.schlick);
		}
		final_color = ft_clr_add(final_color, surface_color);
		final_color = ft_clr_add(final_color, reflect_color);
		final_color = ft_clr_add(final_color, refract_color);
	}
	return final_color;
}

t_clr	ft_reflection(t_comps *comps, t_light *light, t_scene *scene, int recursion_depth)
{
	t_ray	reflection_ray;
	t_clr	res;
	

	res = ft_create_clr(0, 0, 0);
	if (comps->obj->reflective == 0 || recursion_depth == 0)
		return (res);
	reflection_ray.O = comps->over_point;
	reflection_ray.D = comps->reflect;
	
	t_xs xs;
	ft_init_xs(&xs);
	ft_get_intersections(reflection_ray, scene, &xs);	
	
	res = ft_get_color2(&reflection_ray, scene, recursion_depth, &xs, light);

	ft_free_xs(&xs);

	res = ft_clr_sclr_mult(res, comps->obj->reflective);
	return (res);
}

t_clr	ft_get_color2(const t_ray *ray, t_scene *scene, int recursion_depth, t_xs *xs, t_light *light)
{
	t_comps			comps;
	t_intersection	*closest;
	t_clr			ambient;
	t_clr			surface_color;
	t_clr			reflect_color;
	t_clr			refract_color;
	t_clr			final_color;

	ft_bzero(&final_color, sizeof(t_clr));

	closest = ft_closest_intersection(xs);
	if (!closest)
    	return (final_color);
	
	ft_prep_comps(&comps, closest, ray, xs);

	ambient = ft_get_ambient(&scene->ambient, &comps.color);
	surface_color = ft_lighting(&comps, scene, light, &ambient);
	reflect_color = ft_reflection(&comps, light, scene, recursion_depth - 1);
	refract_color = ft_refraction(&comps, light, scene, recursion_depth - 1);
	if (closest->obj->reflective > 0 && closest->obj->transparency > 0)
	{
		reflect_color = ft_clr_sclr_mult(reflect_color, comps.schlick);
		refract_color = ft_clr_sclr_mult(refract_color, 1 - comps.schlick);
	}
	final_color = ft_clr_add(final_color, surface_color);
	final_color = ft_clr_add(final_color, reflect_color);
	final_color = ft_clr_add(final_color, refract_color);
	return (final_color);
}

t_clr	ft_refraction(t_comps *comps, t_light *light, t_scene *scene, int recursion_depth)
{
	t_ray	refraction_ray;
	t_clr	res;
	double	n_ratio;

	res = ft_create_clr(0, 0, 0);
	if (comps->obj->transparency == 0 || recursion_depth == 0)
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
	ft_get_intersections(refraction_ray, scene, &xs);	
	
	res = ft_get_color2(&refraction_ray, scene, recursion_depth, &xs, light);
	
	res = ft_clr_sclr_mult(res, comps->obj->transparency);

	ft_free_xs(&xs);

	return (res);
}
