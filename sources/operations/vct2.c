/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:09:16 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/18 17:52:07 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/miniRT.h"

t_vct	ft_vct_add(const t_vct *a, const t_vct *b)
{
	t_vct	res;

	res.x = a->x + b->x;
	res.y = a->y + b->y;
	res.z = a->z + b->z;
	res.w = a->w + b->w;
	return (res);
}

double	ft_vct_len(const t_vct *a)
{
	return (sqrt(pow(a->x, 2) + pow(a->y, 2) + pow(a->z, 2)));
}

void	ft_vct_scale(t_vct *res, const t_vct *a, double scale)
{
	res->x = a->x * scale;
	res->y = a->y * scale;
	res->z = a->z * scale;
	res->w = a->w * scale;
}

void	ft_vct_norm(t_vct *a)
{
	t_vct	tmp;
	double	len;	

	len = ft_vct_len(a);
	if (len < EPSILON)
		return ;
	ft_vct_scale(&tmp, a, 1 / len);
	tmp.w = 0;
	*a = tmp;
}

void	ft_vct_cross_prod(t_vct *res, const t_vct *a, const t_vct *b)
{
	res->x = a->y * b->z - a->z * b->y;
	res->y = a->z * b->x - a->x * b->z;
	res->z = a->x * b->y - a->y * b->x;
	res->w = 0;
}
