/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lopoka@student.hive.fi>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:55:43 by lucas             #+#    #+#             */
/*   Updated: 2024/08/14 12:45:59 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

void	ft_closest_intersection(t_vct O, t_vct D, t_shape *shape_arr, float t_min, float t_max, float *t_closest, t_shape **shape_closest);

int ft_pixel(int r, int g, int b, int a)
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

t_clr	ft_light(t_clr color, t_shape *shape_arr, t_light *light_arr, t_vct P, t_vct N, t_vct V, float s)
{
	float	i;
	t_vct	L;
	t_vct	R;
	float	n_dot_l;
	float	r_dot_v;

	i = 0;
	for (int j = 0; j < 3; j++)
	{
		if (light_arr[j].type == t_ambient)
		{
			i += light_arr[j].intensity;
			continue ;
		}
		if (light_arr[j].type == t_point)
			L = ft_vct_subtraction(light_arr[j].position, P);
		else
			L = light_arr[j].direction;
		
		// Shadow
		float		t_shdw_closest = FLT_MAX;
		t_shape		*shdw_closest = NULL;

		ft_closest_intersection(P, L, shape_arr, 0.001, 10000, &t_shdw_closest, &shdw_closest);
		if (shdw_closest)
			continue ;

		// Diffuse
		n_dot_l = ft_dot_prod(N, L);
		if (n_dot_l > 0)
			i += light_arr[j].intensity * n_dot_l / (ft_vct_len(N) * ft_vct_len(L));
		
		// Specular
		if (s != -1)
		{
			R = ft_vct_subtraction(ft_vct_sclr_mult(N, 2 * n_dot_l), L);
			r_dot_v = ft_dot_prod(R, V);
			if (r_dot_v > 0)
				i += light_arr[j].intensity * pow(r_dot_v / (ft_vct_len(R) * ft_vct_len(V)), s);
		}
	}
	color.r = ft_modify_channel(color.r, i);
	color.g = ft_modify_channel(color.g, i);
	color.b = ft_modify_channel(color.b, i);
	return (color);
}

int	ft_clr_to_int(t_clr clr)
{
    return (ft_pixel(clr.r, clr.g, clr.b, 255));
}

void	ft_check_closest_sphere(t_shape *shape, float t, float t_min, float t_max, float *t_closest, t_shape **shape_closest)
{
	if ((t >= t_min && t <= t_max) && t < *t_closest)
	{
		*t_closest = t;
		*shape_closest = shape;
	}
}

void	ft_closest_intersection(t_vct O, t_vct D, t_shape *shape_arr, float t_min, float t_max, float *t_closest, t_shape **shape_closest)
{
	for (int i = 0; i < 4; i++)
	{
    	t_vct	CO = ft_vct_subtraction(O, shape_arr[i].position);
    	float	a = ft_dot_prod(D, D);
    	float	b = 2 * ft_dot_prod(CO, D);
    	float	c = ft_dot_prod(CO, CO) - (shape_arr[i].radius * shape_arr[i].radius);

    	float discr = b * b - 4 * a * c;
    	if (discr < 0)
			continue ;
		ft_check_closest_sphere(&(shape_arr[i]), (-b + sqrt(discr)) / (2 * a), t_min, t_max, t_closest, shape_closest);
		ft_check_closest_sphere(&(shape_arr[i]), (-b - sqrt(discr)) / (2 * a), t_min, t_max, t_closest, shape_closest);
	}
}

t_vct ft_reflect_ray(t_vct R, t_vct N)
{
	return (ft_vct_subtraction(ft_vct_sclr_mult(N, 2 * ft_dot_prod(N, R)), R));
}

t_clr	ft_trace_ray(t_vct O, t_vct D, t_shape *shape_arr, t_light *light_arr, float t_min, float t_max, int recursion_depth)
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
	t_shape		*shape_arr;
	t_light		*light_arr;

	
	shape_arr = malloc(4 * sizeof(t_shape));
	shape_arr[0].position = ft_create_vct(0, -1, 3);
	shape_arr[0].radius = 1;
	shape_arr[0].color = ft_create_clr(255, 0, 0);
	shape_arr[0].specular = 500;
	shape_arr[0].reflective = 0.2;

	shape_arr[1].position = ft_create_vct(2, 0, 4);
	shape_arr[1].radius = 1;
	shape_arr[1].color = ft_create_clr(0, 0, 255);
	shape_arr[1].specular = 500;
	shape_arr[1].reflective = 0.3;

	shape_arr[2].position = ft_create_vct(-2, 0, 4);
	shape_arr[2].radius = 1;
	shape_arr[2].color = ft_create_clr(0, 255, 0);
	shape_arr[2].specular = 500;
	shape_arr[2].reflective = 0.4;
	
	shape_arr[3].position = ft_create_vct(0, -5001, 0);
	shape_arr[3].radius = 5000;
	shape_arr[3].color = ft_create_clr(255, 255, 0);
	shape_arr[3].specular = 1000;
	shape_arr[3].reflective = 0.5;

	// Lights
	light_arr = calloc(3, sizeof(t_light));

	light_arr[0].type = t_ambient;
	light_arr[0].intensity = 0.2;
	
	light_arr[1].type = t_point;
	light_arr[1].intensity = 0.6;
	light_arr[1].position = ft_create_vct(2, 1, 0);
	

	light_arr[2].type = t_directional;
	light_arr[2].intensity = 0.2;
	light_arr[2].direction = ft_create_vct(1, 4, 4);


	O = ft_create_vct(0, 0, 0);
	row = 0;
	while (row < CANV_HGHT)
	{
		col = 0;
		while (col < CANV_WDTH)
		{
			D = ft_canv_to_view(col, CANV_HGHT - 1 - row);
			color = ft_trace_ray(O, D, shape_arr, light_arr, 1, 100000, 3);
			mlx_put_pixel(mrt->img, col++, row, ft_clr_to_int(color));
		}
		row++;
	}

	free(shape_arr);
	free(light_arr);

	mlx_image_to_window(mrt->mlx, mrt->img, 0, 0);
}
