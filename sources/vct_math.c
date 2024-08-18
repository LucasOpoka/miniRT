/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:45:19 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/18 14:29:51 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

t_vct	ft_create_vct(float x, float y, float z)
{
	t_vct	v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = 0;
	return (v);
}

float	ft_vct_dot(t_vct a, t_vct b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vct	ft_vct_sclr_mult(t_vct a, float b)
{	
	return (ft_create_vct(a.x * b, a.y * b, a.z * b));	
}

t_vct	ft_vct_sclr_div(t_vct a, float b)
{	
	return (ft_create_vct(a.x / b, a.y / b, a.z / b));	
}

t_vct	ft_vct_neg(t_vct a)
{	
	return (ft_create_vct(-a.x, -a.y, -a.z));	
}

t_vct	ft_vct_sub(t_vct a, t_vct b)
{
	return (ft_create_vct(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vct	ft_vct_add(t_vct a, t_vct b)
{
	return (ft_create_vct(a.x + b.x, a.y + b.y, a.z + b.z));
}

float	ft_vct_len(t_vct a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

void	ft_vct_scale(t_vct *res, t_vct *a, float scale)
{
	res->x = a->x * scale;
	res->y = a->y * scale;
	res->z = a->z * scale;
	res->w = a->w * scale;
}

void	ft_vct_norm(t_vct *a)
{
	t_vct	tmp;
	float	len;	

	len = ft_vct_len(*a);
	ft_vct_scale(&tmp, a, 1 / len);
	tmp.w = 0;
	*a = tmp;
		
	//ft_vct_scale(a, a, 1 / ft_vct_len(*a));
	//a->w = 0;
}

// Calculate cross product of two vectors
// https://byjus.com/maths/cross-product/
void	ft_vct_cross_prod(t_vct *res, t_vct a, t_vct b)
{
	res->x = a.y * b.z - a.z * b.y;
	res->y = a.z * b.x - a.x * b.z;
	res->z = a.x * b.y - a.y * b.x;
	res->w = 0;
}
