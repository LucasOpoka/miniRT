/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clr1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:57:59 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/03 10:29:05 by lopoka           ###   ########.fr       */
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
