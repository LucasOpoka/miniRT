/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lopoka@student.hive.fi>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:55:43 by lucas             #+#    #+#             */
/*   Updated: 2024/08/05 13:59:44 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

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

t_vct	ft_vct_subtraction(t_vct a, t_vct b)
{
	return (ft_create_vct(a.x - b.x, a.y - b.y, a.z - b.z));
}

void	ft_check_closest_sphere(t_sphere *sphr, float t, float t_min, float t_max, float *t_closest, t_sphere **sphr_closest)
{
	if ((t >= t_min && t <= t_max) && t < *t_closest)
	{
		*t_closest = t;
		*sphr_closest = sphr;
	}
}

int	ft_intersect_ray_sphere(t_vct O, t_vct D, t_sphere *sphr, float t_min, float t_max, float *t_closest, t_sphere **sphr_closest)
{
	for (int i = 0; i < 3; i++)
	{
    	t_vct	CO = ft_vct_subtraction(O, sphr[i].position);
    	float	a = ft_dot_prod(D, D);
    	float	b = 2 * ft_dot_prod(CO, D);
    	float	c = ft_dot_prod(CO, CO) - (sphr[i].radius * sphr[i].radius);

    	float discr = b * b - 4 * a * c;
    	if (discr < 0)
			continue ;
		ft_check_closest_sphere(&(sphr[i]), (-b + sqrt(discr)) / (2 * a), t_min, t_max, t_closest, sphr_closest);
		ft_check_closest_sphere(&(sphr[i]), (-b - sqrt(discr)) / (2 * a), t_min, t_max, t_closest, sphr_closest);
	}
	if (*sphr_closest)
		return (sphr_closest[0]->color);
    return (ft_pixel(0, 0, 0, 0));
}

int	ft_trace_ray(t_vct O, t_vct D, t_sphere *sphr_arr, float t_min, float t_max, t_sphere **sphr_closest)
{
	float		t_closest;

	*sphr_closest = NULL;
	t_closest = FLT_MAX;
	return (ft_intersect_ray_sphere(O, D, sphr_arr, t_min, t_max, &t_closest, sphr_closest));
}

void	ft_show_img(t_mrt *mrt)
{
	t_vct	O;
	t_vct	D;
	int		color;
	int		row;
	int		col;
	t_sphere	*sphr_arr;
	t_sphere	**sphr_closest;

	sphr_closest = malloc(sizeof(t_sphere *));
	
	sphr_arr = malloc(3 * sizeof(t_sphere));
	sphr_arr[0].position = ft_create_vct(0, 0, 4);
	sphr_arr[0].radius = 0.5;
	sphr_arr[0].color = ft_pixel(227, 61, 148, 255);

	sphr_arr[1].position = ft_create_vct(1, 0, 4);
	sphr_arr[1].radius = 0.5;
	sphr_arr[1].color = ft_pixel(234, 239, 44, 255);

	sphr_arr[2].position = ft_create_vct(-1, 0, 4);
	sphr_arr[2].radius = 0.5;
	sphr_arr[2].color = ft_pixel(90, 34, 139, 255);

	O = ft_create_vct(0, 0, 0);
	row = 0;
	while (row < CANV_HGHT)
	{
		col = 0;
		while (col < CANV_WDTH)
		{
			D = ft_canv_to_view(col, row);
			color = ft_trace_ray(O, D, sphr_arr, 1, 100000, sphr_closest); 
			mlx_put_pixel(mrt->img, col++, row, color);
		}
		row++;
	}
	free(sphr_arr);
	free(sphr_closest);
	mlx_image_to_window(mrt->mlx, mrt->img, 0, 0);
}
