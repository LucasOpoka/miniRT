/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:07:43 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/12 21:11:26 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/miniRT.h"

t_ptrn	ft_ptrn(t_clr (f)(double *uv, double w, double h), double w, double h)
{
	t_ptrn	ptrn;

	ptrn.ptrn_func = f;
	ptrn.width = w;
	ptrn.height = h;
	return (ptrn);
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
