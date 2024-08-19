/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lopoka@student.hive.fi>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:55:43 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/18 14:19:50 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

void	ft_closest_intersection(t_vct O, t_vct D, t_scene *scene, float t_min, float t_max, float *t_closest, t_shape **shape_closest);

uint32_t ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

t_clr	ft_create_clr(float r, float g, float b)
{
	t_clr	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

t_vct	ft_pixel_to_ray(float pixel_x, float pixel_y, t_camera camera, t_vct *ray_origin_world)
{	
	t_vct	ray_pixel_camera;
	t_vct	ray_pixel_world;
	t_vct	ray_origin_camera;

	ray_pixel_camera.x = camera.half_wdth - (pixel_x + 0.5) * camera.pixel_size;
	ray_pixel_camera.y = camera.half_hght - (pixel_y + 0.5) * camera.pixel_size;
	ray_pixel_camera.z = -1;
	ray_pixel_camera.w = 1;
	ft_bzero(&ray_origin_camera, sizeof(t_vct));
	ray_origin_camera.w = 1;
	ft_vct_mtrx_mult(ray_origin_world, camera.camera_to_world, ray_origin_camera);
	ft_vct_mtrx_mult(&ray_pixel_world, camera.camera_to_world, ray_pixel_camera);
	t_vct Dir = ft_vct_sub(ray_pixel_world, *ray_origin_world);
	Dir.w = 0;
	ft_vct_norm(&Dir);
	return (Dir);
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

uint32_t	ft_clr_to_int(t_clr clr)
{
    return (ft_pixel(clr.r, clr.g, clr.b, 255));
}

void	ft_check_closest_shape(t_shape *shape, float t, float t_min, float t_max, float *t_closest, t_shape **shape_closest)
{
	if ((t >= t_min && t <= t_max) && t < *t_closest)
	{
		*t_closest = t;
		*shape_closest = shape;
	}
}

void	ft_closest_intersection(t_vct O, t_vct D, t_scene *scene, float t_min, float t_max, float *t_closest, t_shape **shape_closest)
{
	t_shape	*shape;
	size_t	i;
	
	i = 0;
	while (i < scene->shapes.i)
	{
		shape = (t_shape *) scene->shapes.arr[i++];
		if (shape->type == t_sphere)
		{
			t_vct	CO = ft_vct_sub(O, shape->position);
			float	a = ft_vct_dot(D, D);
			float	b = 2 * ft_vct_dot(CO, D);
			float	c = ft_vct_dot(CO, CO) - (shape->radius * shape->radius);

			float discr = b * b - 4 * a * c;
			if (discr < 0)
				continue ;
			ft_check_closest_shape(shape, (-b + sqrt(discr)) / (2 * a), t_min, t_max, t_closest, shape_closest);
			ft_check_closest_shape(shape, (-b - sqrt(discr)) / (2 * a), t_min, t_max, t_closest, shape_closest);
		}
		if (shape->type == t_plane)
		{
			float	denom = ft_vct_dot(D, shape->orientation);
			if (fabs(denom) < 0.0001)
				continue ;
			ft_check_closest_shape(shape, ft_vct_dot(ft_vct_sub(shape->position, O), shape->orientation) / denom, t_min, t_max, t_closest, shape_closest);
		}
	}
}

t_vct ft_reflect_ray(t_vct R, t_vct N)
{
	return (ft_vct_sub(ft_vct_sclr_mult(N, 2 * ft_vct_dot(N, R)), R));
}

t_clr	ft_trace_ray(t_vct O, t_vct D, t_scene *scene, float t_min, float t_max, int recursion_depth)
{
	float		t_closest = FLT_MAX;
	t_shape		*shape_closest = NULL;
	t_clr		local_color;
	t_clr		reflected_color;
	float		rfl;


	ft_closest_intersection(O, D, scene, t_min, t_max, &t_closest, &shape_closest);

	if (!shape_closest)
    	return (ft_create_clr(0, 0, 0));
	
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
	reflected_color = ft_trace_ray(P, ft_reflect_ray(ft_vct_neg(D) , N), scene , t_min, t_max, recursion_depth - 1);

	local_color.r = local_color.r  * (1 - rfl) + reflected_color.r * rfl;
	local_color.g = local_color.g  * (1 - rfl) + reflected_color.g * rfl;
	local_color.b = local_color.b  * (1 - rfl) + reflected_color.b * rfl;	
	
	return (local_color);
}


void	ft_show_img(t_mrt *mrt)
{
	t_vct		O;
	t_vct		D;
	t_clr		color;
	int			pixel_x;
	int			pixel_y;

	// Test scene
	t_scene scene = get_test_scene();


	ft_init_camera(&scene.camera);
	ft_set_camera_matrices(&scene.camera);

	pixel_y = 0;
	while (pixel_y < CANV_HGHT)
	{
		pixel_x = 0;
		while (pixel_x < CANV_WDTH)
		{
			D = ft_pixel_to_ray(pixel_x, pixel_y, scene.camera, &O);
			color = ft_trace_ray(O, D, &scene, 1, 100000, 3);
			mlx_put_pixel(mrt->img, pixel_x++, pixel_y, ft_clr_to_int(color));
		}
		pixel_y++;
	}

	ft_free_void_arr(&scene.shapes);
	ft_free_void_arr(&scene.lights);

	mlx_image_to_window(mrt->mlx, mrt->img, 0, 0);
}
