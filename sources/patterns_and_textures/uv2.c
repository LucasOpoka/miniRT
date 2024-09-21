/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:07:43 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/16 12:43:03 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/miniRT.h"

void	ft_conical_map(double *uv, t_vct *p)
{
	double	theta;
	double	radius;

	radius = pow(p->x, 2) + pow(p->z, 2);
	theta = atan2(p->x, p->z);
	uv[0] = 1 - ((theta / (2 * M_PI)) + 0.5);
	uv[1] = fmod(sqrt(radius), 1);
}

void	ft_triangle_map(double *uv, t_vct *p)
{
	uv[0] = (float) fmod(p->x, 1.0);
	uv[1] = (float) fmod(p->z, 1.0) + fmod(p->y, 1);
}
