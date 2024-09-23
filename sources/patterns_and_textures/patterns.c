/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:07:43 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/23 15:58:49 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/miniRT.h"

t_ptrn	ft_ptrn(void *f, double w, double h)
{
	t_ptrn	ptrn;

	ptrn.ptrn_func = f;
	ptrn.wdth = w;
	ptrn.hght = h;
	return (ptrn);
}

void	ft_checkers(double *uv, double width, double height, t_comps *comps)
{
	int		uv2[2];

	uv2[0] = (int) floor(uv[0] * width);
	uv2[1] = (int) floor(uv[1] * height);
	if ((uv2[0] + uv2[1]) % 2 == 0)
		comps->color = ft_create_clr(0, 0, 0);
	else
		comps->color = ft_create_clr(255, 255, 255);
}

void	ft_arches(double *uv, double width, double height, t_comps *comps)
{
	double	uv2[2];

	uv2[0] = pow(uv[0] * width, 2);
	uv2[1] = pow(uv[1] * height, 2);
	if ((int) sqrt(uv2[0] + uv2[1]) % 2 == 0)
		comps->color = ft_create_clr(0, 0, 0);
	else
		comps->color = ft_create_clr(255, 255, 255);
}

void	ft_rings(double *uv, double width, double height, t_comps *comps)
{
	double	uv2[2];

	uv2[0] = pow((fabs(uv[0]) - 0.5) * width, 2);
	uv2[1] = pow((fabs(uv[1]) - 0.5) * height, 2);
	if ((int) sqrt(uv2[0] + uv2[1]) % 2 == 0)
		comps->color = ft_create_clr(0, 0, 0);
	else
		comps->color = ft_create_clr(255, 255, 255);
}
