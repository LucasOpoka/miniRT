/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:45:19 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/04 19:56:17 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

t_vct	ft_create_vct(double x, double y, double z)
{
	t_vct	v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = 0;
	return (v);
}

double	ft_vct_dot(const t_vct *a, const t_vct *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w);
}

t_vct	ft_vct_x_sclr(const t_vct *a, double b)
{
	t_vct	res;

	res.x = a->x * b;
	res.y = a->y * b;
	res.z = a->z * b;
	res.w = a->w * b;
	return (res);
}

t_vct	ft_vct_neg(const t_vct *a)
{
	t_vct	res;

	res.x = -a->x;
	res.y = -a->y;
	res.z = -a->z;
	res.w = -a->w;
	return (res);
}

t_vct	ft_vct_sub(const t_vct *a, const t_vct *b)
{
	t_vct	res;

	res.x = a->x - b->x;
	res.y = a->y - b->y;
	res.z = a->z - b->z;
	res.w = a->w - b->w;
	return (res);
}
