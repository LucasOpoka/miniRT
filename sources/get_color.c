/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:47:05 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/26 17:17:01 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

t_clr	ft_get_color(const t_ray *ray, t_scene *scene, int recursion_depth, t_void_arr *intersections)
{
	t_comps			comps;
	(void)			recursion_depth;
	t_intersection	*closest;
	t_clr			ambient;
	t_clr			surface_color;
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
		final_color = ft_clr_add(surface_color, final_color);
	}
	return final_color;
}
