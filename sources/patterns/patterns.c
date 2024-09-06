/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:07:43 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/06 14:37:59 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/miniRT.h"

void	ft_spherical_map(double *uv, t_vct *p)
{
	double	theta;
	double	phi;
	double	radius;
	double	raw_u;

	theta = atan2(p->x, p->z);
	radius = ft_vct_len(p);
	phi = acos(p->y / radius);
	raw_u = theta / (2 * M_PI);
	uv[0] = 1 - (raw_u + 0.5);
	uv[1] = 1 - phi / M_PI;
}

void	ft_planar_map(double *uv, t_vct *p)
{
	uv[0] = fmod(p->x, 1.0);
	uv[1] = fmod(p->z, 1.0);
}

t_clr	ft_checkers(double *uv, double width, double height)
{
	int		uv2[2];
	t_clr	clr;

	uv2[0] = (int) floor(uv[0] * width);
	uv2[1] = (int) floor(uv[1] * height);
	if ((uv2[0] + uv2[1]) % 2 == 0)
		clr = ft_create_clr(0, 0, 0);
	else
		clr = ft_create_clr(255, 255, 255);
	return (clr);
}
