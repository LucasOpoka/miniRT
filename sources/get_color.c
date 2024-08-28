/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:47:05 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/28 15:38:25 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

t_clr	ft_reflection(t_comps *comps, t_light *light, t_scene *scene, int recursion_depth);
t_clr	ft_get_color2(const t_ray *ray, t_scene *scene, int recursion_depth, t_void_arr *intersections, t_light *light);


t_clr	ft_get_color(const t_ray *ray, t_scene *scene, int recursion_depth, t_void_arr *intersections)
{
	t_comps			comps;
	t_intersection	*closest;
	t_clr			ambient;
	t_clr			surface_color;
	t_clr			reflect_color;
	size_t			i;
	t_light			*light;
	t_clr			final_color;

	ft_bzero(&final_color, sizeof(t_clr));

	closest = ft_closest_intersection(intersections);
	if (!closest)
    	return (ft_create_clr(0, 0, 0));

	ft_prepare_computations(&comps, closest, ray);
	
	ambient = ft_get_ambient(&scene->ambient, &closest->shape->color);

	i = 0;
	while (i < scene->lights.i)
	{
		light = (t_light *) scene->lights.arr[i++];
		surface_color = ft_lighting(&comps, scene, light, &ambient);
		reflect_color = ft_reflection(&comps, light, scene, recursion_depth);
		final_color = ft_clr_add(final_color, surface_color);
		final_color = ft_clr_add(final_color, reflect_color);
	}
	return final_color;
}

t_clr	ft_reflection(t_comps *comps, t_light *light, t_scene *scene, int recursion_depth)
{
	t_ray	reflection_ray;
	t_clr	res;
	

	res = ft_create_clr(0, 0, 0);
	if (comps->shape->reflective == 0 || recursion_depth == 0)
		return (res);
	reflection_ray.O = comps->over_point;
	reflection_ray.D = comps->reflect;
	
	t_void_arr intersections;
	ft_init_void_arr(&intersections);
	ft_get_intersections(reflection_ray, scene, &intersections);	
	
	res = ft_get_color2(&reflection_ray, scene, recursion_depth, &intersections, light);

	ft_free_void_arr(&intersections);

	res = ft_clr_sclr_mult(res, comps->shape->reflective);
	return (res);
}

t_clr	ft_get_color2(const t_ray *ray, t_scene *scene, int recursion_depth, t_void_arr *intersections, t_light *light)
{
	t_comps			comps;
	t_intersection	*closest;
	t_clr			ambient;
	t_clr			surface_color;
	t_clr			reflect_color;
	t_clr			final_color;

	ft_bzero(&final_color, sizeof(t_clr));

	closest = ft_closest_intersection(intersections);
	if (!closest)
    	return (final_color);

	ft_prepare_computations(&comps, closest, ray);
	
	ambient = ft_get_ambient(&scene->ambient, &closest->shape->color);
	surface_color = ft_lighting(&comps, scene, light, &ambient);
	reflect_color = ft_reflection(&comps, light, scene, recursion_depth - 1);
	final_color = ft_clr_add(final_color, surface_color);
	final_color = ft_clr_add(final_color, reflect_color);
	return (final_color);
}
