/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:47:05 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/23 13:07:33 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

t_clr	ft_get_color(t_vct O, t_vct D, t_scene *scene, float t_min, float t_max, int recursion_depth, float t_closest, t_shape *shape_closest)
{
	//t_clr		local_color;
	//t_clr		reflected_color;
	//float		rfl;

	(void) O;
	(void) D;
	(void) scene;
	(void) t_min;
	(void) t_max;
	(void) recursion_depth;
	(void) t_closest;

	if (!shape_closest)
    	return (ft_create_clr(0, 0, 0));
	return shape_closest->color;
}
/*
	// Light
	t_vct P = ft_vct_add(O, ft_vct_sclr_mult(D, t_closest));
	t_vct N = ft_vct_sub(P, shape_closest->position);
	N = ft_vct_sclr_div(N, ft_vct_len(N));
	if (shape_closest->type == t_plane)
	{
		N = shape_closest->orientation;
		N = ft_vct_sclr_div(N, ft_vct_len(N));
	}

	local_color = ft_light(shape_closest->color, scene, P, N, ft_vct_neg(D), shape_closest->specular);

	// Reflected color
	rfl = shape_closest->reflective;
	if (!recursion_depth || rfl <= 0)
		return (local_color);

	float		t_closest_refl = FLT_MAX;
	t_shape		*shape_closest_refl = NULL;

	ft_closest_intersection(P, ft_reflect_ray(ft_vct_neg(D), N), scene, t_min, t_max, &t_closest_refl, &shape_closest_refl);
	reflected_color = ft_get_color(P, ft_reflect_ray(ft_vct_neg(D) , N), scene , t_min, t_max, recursion_depth - 1, t_closest_refl, shape_closest_refl);

	local_color.r = local_color.r  * (1 - rfl) + reflected_color.r * rfl;
	local_color.g = local_color.g  * (1 - rfl) + reflected_color.g * rfl;
	local_color.b = local_color.b  * (1 - rfl) + reflected_color.b * rfl;	
	
	return (local_color);
}


t_clr	ft_light(t_clr color, t_scene *scene, t_vct P, t_vct N, t_vct V, float s)
{
	float	light_intensity;
	t_vct	L;
	t_vct	R;
	float	n_dot_l;
	float	r_dot_v;
	t_light	*light;
	size_t	i;

	light_intensity = 0;
	i = 0;
	while (i < scene->lights.i)
	{
		light = scene->lights.arr[i++];

		if (light->type == t_ambient)
		{
			light_intensity += light->intensity;
			continue ;
		}
		if (light->type == t_point)
			L = ft_vct_sub(light->position, P);
		else
			L = light->direction;
		
		// Shadow
		float		t_shdw_closest = FLT_MAX;
		t_shape		*shdw_closest = NULL;

		ft_closest_intersection(P, L, scene, 0.001, 10000, &t_shdw_closest, &shdw_closest);
		if (shdw_closest)
			continue ;

		// Diffuse
		n_dot_l = ft_vct_dot(N, L);
		if (n_dot_l > 0)
			light_intensity += light->intensity * n_dot_l / (ft_vct_len(N) * ft_vct_len(L));
		
		// Specular
		if (s != -1)
		{
			R = ft_vct_sub(ft_vct_sclr_mult(N, 2 * n_dot_l), L);
			r_dot_v = ft_vct_dot(R, V);
			if (r_dot_v > 0)
				light_intensity += light->intensity * pow(r_dot_v / (ft_vct_len(R) * ft_vct_len(V)), s);
		}
	}
	
	color.r = ft_modify_channel(color.r, light_intensity);
	color.g = ft_modify_channel(color.g, light_intensity);
	color.b = ft_modify_channel(color.b, light_intensity);
	return (color);
}
*/

uint32_t ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	ft_clr_to_int(t_clr clr)
{
    return (ft_pixel(clr.r, clr.g, clr.b, 255));
}

t_clr	ft_create_clr(float r, float g, float b)
{
	t_clr	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

float	ft_modify_channel(float ch, float i)
{
	ch = ch * i;
	if (ch < 0)
		return (0);
	if (ch > 255)
		return (255);
	return (ch);
}
