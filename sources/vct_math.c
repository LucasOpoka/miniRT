/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:45:19 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/30 12:43:14 by lucas            ###   ########.fr       */
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

t_vct	ft_vct_sclr_mult(const t_vct *a, double b)
{
	t_vct res;

	res.x = a->x * b;
	res.y = a->y * b;
	res.z = a->z * b;
	res.w = a->w * b;
	return (res);	
}

t_vct	ft_vct_neg(const t_vct *a)
{	
	t_vct res;

	res.x = -a->x;
	res.y = -a->y;
	res.z = -a->z;
	res.w = -a->w;
	return (res);

}

t_vct	ft_vct_sub(const t_vct *a, const t_vct *b)
{
	t_vct res;

	res.x = a->x - b->x;
	res.y = a->y - b->y;
	res.z = a->z - b->z;
	res.w = a->w - b->w;
	return (res);

}

t_vct	ft_vct_add(const t_vct *a, const t_vct *b)
{
	t_vct res;

	res.x = a->x + b->x;
	res.y = a->y + b->y;
	res.z = a->z + b->z;
	res.w = a->w + b->w;
	return (res);
}

double	ft_vct_len(const t_vct *a)
{
	return (sqrt(a->x * a->x + a->y * a->y + a->z * a->z));
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

// Calculate cross product of two vectors
// https://byjus.com/maths/cross-product/
void	ft_vct_cross_prod(t_vct *res, const t_vct *a, const t_vct *b)
{
	res->x = a->y * b->z - a->z * b->y;
	res->y = a->z * b->x - a->x * b->z;
	res->z = a->x * b->y - a->y * b->x;
	res->w = 0;
}
