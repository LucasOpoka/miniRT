/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lopoka@student.hive.fi>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:55:43 by lucas             #+#    #+#             */
/*   Updated: 2024/08/15 16:22:16 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

void	ft_closest_intersection(t_vct O, t_vct D, t_void_arr *shape_arr, float t_min, float t_max, float *t_closest, t_shape **shape_closest);

uint32_t ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

t_vct	ft_create_vct(float x, float y, float z)
{
	t_vct	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_clr	ft_create_clr(float r, float g, float b)
{
	t_clr	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}


t_vct	ft_canv_to_view(int x, int y)
{
	t_vct	v;
	
	v.x = (float) x * VIEW_WDTH / CANV_WDTH - 0.5;
	v.y = (float) y * VIEW_HGHT / CANV_HGHT - 0.5;
	v.z	= (float) DISTANCE;
	return (v);
}

float	ft_dot_prod(t_vct a, t_vct b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vct	ft_vct_sclr_mult(t_vct a, float b)
{	
	return (ft_create_vct(a.x * b, a.y * b, a.z * b));	
}

t_vct	ft_vct_sclr_div(t_vct a, float b)
{	
	return (ft_create_vct(a.x / b, a.y / b, a.z / b));	
}

float	ft_vct_len(t_vct a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vct	ft_vct_neg(t_vct a)
{	
	return (ft_create_vct(-a.x, -a.y, -a.z));	
}

t_vct	ft_vct_subtraction(t_vct a, t_vct b)
{
	return (ft_create_vct(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vct	ft_vct_add(t_vct a, t_vct b)
{
	return (ft_create_vct(a.x + b.x, a.y + b.y, a.z + b.z));
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

t_clr	ft_light(t_clr color, t_void_arr *shape_arr, t_void_arr *light_arr, t_vct P, t_vct N, t_vct V, float s)
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
	while (i < light_arr->i)
	{
		light = light_arr->arr[i++];

		if (light->type == t_ambient)
		{
			light_intensity += light->intensity;
			continue ;
		}
		if (light->type == t_point)
			L = ft_vct_subtraction(light->position, P);
		else
			L = light->direction;
		
		// Shadow
		float		t_shdw_closest = FLT_MAX;
		t_shape		*shdw_closest = NULL;

		ft_closest_intersection(P, L, shape_arr, 0.001, 10000, &t_shdw_closest, &shdw_closest);
		if (shdw_closest)
			continue ;

		// Diffuse
		n_dot_l = ft_dot_prod(N, L);
		if (n_dot_l > 0)
			light_intensity += light->intensity * n_dot_l / (ft_vct_len(N) * ft_vct_len(L));
		
		// Specular
		if (s != -1)
		{
			R = ft_vct_subtraction(ft_vct_sclr_mult(N, 2 * n_dot_l), L);
			r_dot_v = ft_dot_prod(R, V);
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

void	ft_closest_intersection(t_vct O, t_vct D, t_void_arr *shape_arr, float t_min, float t_max, float *t_closest, t_shape **shape_closest)
{
	t_shape	*shape;
	size_t	i;
	
	i = 0;
	while (i < shape_arr->i)
	{
		shape = (t_shape *) shape_arr->arr[i++];
		if (shape->type == t_sphere)
		{
			t_vct	CO = ft_vct_subtraction(O, shape->position);
			float	a = ft_dot_prod(D, D);
			float	b = 2 * ft_dot_prod(CO, D);
			float	c = ft_dot_prod(CO, CO) - (shape->radius * shape->radius);

			float discr = b * b - 4 * a * c;
			if (discr < 0)
				continue ;
			ft_check_closest_shape(shape, (-b + sqrt(discr)) / (2 * a), t_min, t_max, t_closest, shape_closest);
			ft_check_closest_shape(shape, (-b - sqrt(discr)) / (2 * a), t_min, t_max, t_closest, shape_closest);
		}
		if (shape->type == t_plane)
		{
			float	denom = ft_dot_prod(D, shape->orientation);
			if (fabs(denom) < 0.0001)
				continue ;
			ft_check_closest_shape(shape, ft_dot_prod(ft_vct_subtraction(shape->position, O), shape->orientation) / denom, t_min, t_max, t_closest, shape_closest);
		}
	}
}

t_vct ft_reflect_ray(t_vct R, t_vct N)
{
	return (ft_vct_subtraction(ft_vct_sclr_mult(N, 2 * ft_dot_prod(N, R)), R));
}

t_clr	ft_trace_ray(t_vct O, t_vct D, t_void_arr *shape_arr, t_void_arr *light_arr, float t_min, float t_max, int recursion_depth)
{
	float		t_closest = FLT_MAX;
	t_shape		*shape_closest = NULL;
	t_clr		local_color;
	t_clr		reflected_color;
	float		rfl;


	ft_closest_intersection(O, D, shape_arr, t_min, t_max, &t_closest, &shape_closest);

	if (!shape_closest)
    	return (ft_create_clr(0, 0, 0));
	
	// Light
	t_vct P = ft_vct_add(O, ft_vct_sclr_mult(D, t_closest));
	t_vct N = ft_vct_subtraction(P, shape_closest->position);
	N = ft_vct_sclr_div(N, ft_vct_len(N));
	if (shape_closest->type == t_plane)
	{
		N = shape_closest->orientation;
		N = ft_vct_sclr_div(N, ft_vct_len(N));
	}

	local_color = ft_light(shape_closest->color, shape_arr, light_arr, P, N, ft_vct_neg(D), shape_closest->specular);

	// Reflected color
	rfl = shape_closest->reflective;
	if (!recursion_depth || rfl <= 0)
		return (local_color);
	reflected_color = ft_trace_ray(P, ft_reflect_ray(ft_vct_neg(D) , N), shape_arr, light_arr , t_min, t_max, recursion_depth - 1);

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
	int			row;
	int			col;
	t_void_arr	light_arr;
	t_void_arr	shape_arr;

	// Shapes
	ft_init_void_arr(&shape_arr);

	t_shape *shape1 = malloc(sizeof(t_shape));
	shape1->type = t_sphere;
	shape1->position = ft_create_vct(0, -1, 3);
	shape1->radius = 1;
	shape1->color = ft_create_clr(255, 0, 0);
	shape1->specular = 500;
	shape1->reflective = 0.2;

	t_shape *shape2 = malloc(sizeof(t_shape));
	shape2->type = t_sphere;
	shape2->position = ft_create_vct(2, 0, 4);
	shape2->radius = 1;
	shape2->color = ft_create_clr(0, 0, 255);
	shape2->specular = 500;
	shape2->reflective = 0.3;

	t_shape *shape3 = malloc(sizeof(t_shape));
	shape3->type = t_sphere;
	shape3->position = ft_create_vct(-2, 0, 4);
	shape3->radius = 1;
	shape3->color = ft_create_clr(0, 255, 0);
	shape3->specular = 500;
	shape3->reflective = 0.4;

	t_shape *shape4 = malloc(sizeof(t_shape));
	shape4->type = t_sphere;
	shape4->position = ft_create_vct(0, -5001, 0);
	shape4->radius = 5000;
	shape4->color = ft_create_clr(255, 255, 0);
	shape4->specular = 1000;
	shape4->reflective = 0.2;

	t_shape *shape5 = malloc(sizeof(t_shape));
	shape5->type = t_plane;
	shape5->position = ft_create_vct(0, 0, 5);
	shape5->color = ft_create_clr(90, 34, 139);
	shape5->orientation = ft_create_vct(0, 1, -1);
	shape5->specular = 1000;
	shape5->reflective = 0.4;
	
	ft_void_arr_add(&shape_arr, shape1);
	ft_void_arr_add(&shape_arr, shape2);
	ft_void_arr_add(&shape_arr, shape3);
	//ft_void_arr_add(&shape_arr, shape4);
	ft_void_arr_add(&shape_arr, shape5);

	// Lights
	ft_init_void_arr(&light_arr);

	t_light *light1 = malloc(sizeof(t_light));
	light1->type = t_ambient;
	light1->intensity = 0.2;

	t_light *light2 = malloc(sizeof(t_light));
	light2->type = t_point;
	light2->intensity = 0.6;
	light2->position = ft_create_vct(2, 1, 0);
	
	t_light *light3 = malloc(sizeof(t_light));
	light3->type = t_directional;
	light3->intensity = 0.2;
	light3->direction = ft_create_vct(1, 4, 4);
	
	ft_void_arr_add(&light_arr, light1);
	ft_void_arr_add(&light_arr, light2);
	ft_void_arr_add(&light_arr, light3);


	O = ft_create_vct(0, 0, 0);
	row = 0;
	while (row < CANV_HGHT)
	{
		col = 0;
		while (col < CANV_WDTH)
		{
			D = ft_canv_to_view(col, CANV_HGHT - 1 - row);
			color = ft_trace_ray(O, D, &shape_arr, &light_arr, 1, 100000, 3);
			mlx_put_pixel(mrt->img, col++, row, ft_clr_to_int(color));
		}
		row++;
	}

	ft_free_void_arr(&shape_arr);
	ft_free_void_arr(&light_arr);

	mlx_image_to_window(mrt->mlx, mrt->img, 0, 0);
}
