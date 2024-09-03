/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:09:25 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/03 11:00:16 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"
#include "../includes/bvh.h"

t_clr	ft_get_ambient(t_ambient *ambient, t_clr *obj_color)
{
	t_clr	temp;
	t_clr	res;

	temp = ft_clr_sclr_mult(*obj_color, ambient->intensity);
	res = ft_clr_clr_mult(temp, ambient->color);
	return (res);
}

int	ft_in_shadow(t_scene *scene, t_light *light, t_vct *over_point)
{
	t_ray	point_to_light;
	float	distance;
	int		res;

	point_to_light.D = ft_vct_sub(&light->pos, over_point);
	distance = ft_vct_len(&point_to_light.D);
	ft_vct_norm(&point_to_light.D);
	point_to_light.O = *over_point;

	//bvh_intersect_ordered(point_to_light, scene, intersect);
	t_xs	xs;
	ft_init_xs(&xs);
	ft_get_intersections(point_to_light, scene, &xs);
	t_intersection	*hit = ft_hit(&xs);
	res = 0;
	if (hit && hit->t < distance)
		res = 1;
	ft_free_xs(&xs);
	return (res);
}

t_clr	ft_lighting(t_comps *comps, t_scene *scene, t_light *light, t_clr *ambient)
{
	t_clr	result;
	t_clr	effective;

	result = *ambient;
	effective = ft_clr_clr_mult(comps->obj->color, light->color);

	// Check if in shadow
	t_vct light_vct = ft_vct_sub(&light->pos, &comps->over_point);
	ft_vct_norm(&light_vct);
	comps->normal.w = 0;
	float light_dot_normal = ft_vct_dot(&light_vct, &comps->normal);
	if (light_dot_normal < 0 || ft_in_shadow(scene, light, &comps->over_point))
		return (result);

	// Diffuse
	t_clr diffuse = ft_clr_sclr_mult(effective, light_dot_normal * comps->obj->diffuse * light->intensity);	

	// Specular
	t_vct neg_light_vct = ft_vct_neg(&light_vct);
	t_vct reflect_vct = ft_reflect(&neg_light_vct, &comps->normal);
	float reflect_dot_eye = ft_vct_dot(&reflect_vct, &comps->eye);
	t_clr specular;
	if (reflect_dot_eye < 0)
		specular = ft_create_clr(0, 0, 0);
	else
		specular = ft_clr_sclr_mult(light->color, light->intensity * comps->obj->specular * pow(reflect_dot_eye, comps->obj->shininess));
	
	result = ft_clr_add(result, diffuse);
	result = ft_clr_add(result, specular);
	return (result);
}
