/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:09:25 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/26 17:12:50 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"
#include "../includes/bvh.h"

t_clr	ft_get_ambient(t_ambient *ambient, t_clr *shape_color)
{
	t_clr	temp;
	t_clr	res;

	temp = ft_clr_sclr_mult(*shape_color, ambient->intensity);
	res = ft_clr_clr_mult(temp, ambient->color);
	return (res);
}

int	ft_in_shadow(t_scene *scene, t_vct *light_vct, t_vct *over_point,
		t_intersects *intersect)
{
	t_ray	point_to_light;
	float	distance;
	int		res;

	distance = ft_vct_len(light_vct);
	point_to_light.D = *light_vct;
	ft_vct_norm(&point_to_light.D);
	point_to_light.O = *over_point;

	bvh_intersect_ordered(point_to_light, scene, intersect);
	//ft_get_intersections(point_to_light, scene, intersect);
	t_intersection	*closest = ft_closest_intersection(intersect);
	res = 1;
	if (!closest || closest->t > distance)
		res = 0;
	return (res);
}

t_clr	ft_lighting(t_comps *comps, t_scene *scene, t_light *light, t_clr *ambient, t_intersects *intersect)
{
	t_clr	result;
	t_clr	effective;

	result = *ambient;
	effective = ft_clr_clr_mult(comps->shape->color, light->color);

	// Check if in shadow
	t_vct light_vct = ft_vct_sub(&light->position, &comps->over_point);
	ft_vct_norm(&light_vct);
	comps->normal.w = 0;
	float light_dot_normal = ft_vct_dot(&light_vct, &comps->normal);
	if (light_dot_normal < 0.1 || ft_in_shadow(scene, &light_vct, &comps->over_point, intersect))
		return (result);

	// Diffuse
	t_clr diffuse = ft_clr_sclr_mult(effective, light_dot_normal * comps->shape->diffuse * light->intensity);	

	// Specular
	t_vct neg_light_vct = ft_vct_neg(&light_vct);
	t_vct reflect_vct = ft_reflect(&neg_light_vct, &comps->normal);
	float reflect_dot_eye = ft_vct_dot(&reflect_vct, &comps->eye);
	t_clr specular;
	if (reflect_dot_eye < 0)
		specular = ft_create_clr(0, 0, 0);
	else
		specular = ft_clr_sclr_mult(light->color, light->intensity * comps->shape->specular * pow(reflect_dot_eye, comps->shape->shininess));
	
	result = ft_clr_add(result, diffuse);
	result = ft_clr_add(result, specular);
	return (result);
}
