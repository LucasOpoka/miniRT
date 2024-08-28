/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clr_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:57:59 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/26 16:41:52 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

t_clr	ft_create_clr(double r, double g, double b)
{
	t_clr	c;

	c.r = r / 255;
	c.g = g / 255;
	c.b = b / 255;
	return (c);
}

t_clr	ft_clr_add(t_clr a, t_clr b)
{
	t_clr	res;

	res.r = a.r + b.r;
	res.g = a.g + b.g;
	res.b = a.b + b.b;
	return (res);
}

t_clr	ft_clr_sclr_mult(t_clr clr, double x)
{
	t_clr	res;

	res.r = clr.r * x;
	res.g = clr.g * x;
	res.b = clr.b * x;
	return (res);
}

t_clr	ft_clr_clr_mult(t_clr a, t_clr b)
{
	t_clr	res;

	res.r = a.r * b.r;
	res.g = a.g * b.g;
	res.b = a.b * b.b;
	return (res);
}

double	ft_clip_color(double clr)
{
	if (clr < 0)
		return (0);
	if (clr > 1)
		return (1);
	return (clr);
}

uint32_t	ft_clr_to_int(t_clr clr)
{
	clr.r = ft_clip_color(clr.r);
	clr.g = ft_clip_color(clr.g);
	clr.b = ft_clip_color(clr.b);
    return (ft_pixel(clr.r * 255, clr.g * 255, clr.b * 255, 255));
}

uint32_t ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

