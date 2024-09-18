/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clr2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:57:59 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/18 17:51:35 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/miniRT.h"

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

uint32_t	ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
