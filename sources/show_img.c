/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lopoka@student.hive.fi>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:55:43 by lucas             #+#    #+#             */
/*   Updated: 2024/08/04 16:46:43 by lucas            ###   ########.fr       */
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

int	ft_intersect_ray_sphere(t_vct O, t_vct D, t_sphere sph, float t_min, float t_max)
{
    t_vct	CO = ft_vct_subtraction(O, sph.position);
    float	a = ft_dot_prod(D, D);
    float	b = 2 * ft_dot_prod(CO, D);
    float	c = ft_dot_prod(CO, CO) - (sph.radius * sph.radius);

    float discr = b * b - 4 * a * c;
    if (discr < 0)
        return (ft_pixel(0, 0, 0, 0));
    float t1 = (-b + sqrt(discr)) / (2 * a);
    float t2 = (-b - sqrt(discr)) / (2 * a);
    if ((t_min < t1 && t1 < t_max) || (t_min < t2 || t2 < t_max))
		return (sph.color);	
    return (ft_pixel(0, 0, 0, 0));
}

int	ft_trace_ray(t_vct O, t_vct D, float t_min, float t_max)
{
	t_sphere	sph;

	sph.position = ft_create_vct(0, 0, 2);
	sph.radius = 0.6;
	sph.color = ft_pixel(227, 61, 148, 255);
	return (ft_intersect_ray_sphere(O, D, sph, t_min, t_max));
}

void	ft_show_img(t_mrt *mrt)
{
	t_vct	O;
	t_vct	D;
	int		color;
	int		row;
	int		col;

	O = ft_create_vct(0, 0, 0);
	row = 0;
	while (row < CANV_HGHT)
	{
		col = 0;
		while (col < CANV_WDTH)
		{
			D = ft_canv_to_view(col, row);
			color = ft_trace_ray(O, D, 1, 100000); 
			mlx_put_pixel(mrt->img, col++, row, color);
		}
		row++;
	}
	mlx_image_to_window(mrt->mlx, mrt->img, 0, 0);
}
