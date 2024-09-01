/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_arr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:58:10 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/01 14:46:20 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

void	ft_init_xs(t_xs *xs)
{
	xs->size = 100;
	xs->to_add = 100;
	xs->i = 0;
	xs->curr = 0;
	xs->arr = (t_intersection *) malloc(xs->size * sizeof(t_intersection));
}

void	ft_xs_realloc(t_xs *xs)
{
	void	*dst;

	if (!xs->arr || xs->i < xs->size - 1)
		return ;
	dst = (t_intersection *) malloc((xs->size + xs->to_add) * sizeof(t_intersection));
	if (!dst)
		return (ft_free_xs(xs));
	ft_memmove(dst, xs->arr, xs->size * sizeof(t_intersection));
	free(xs->arr);
	xs->arr = dst;
	xs->size += xs->to_add;
}

void	ft_add_intersection(t_xs *xs, t_shape *shape, double t)
{
	t_intersection	*intr;

	ft_xs_realloc(xs);
	if (!xs->arr)
		return ;
	intr = &xs->arr[xs->i];
	intr->shape = shape;
	intr->t = t;
	xs->i++;
}

void	ft_free_xs(t_xs *xs)
{
	if (!xs->arr)
		return ;
	free(xs->arr);
	xs->arr = 0;
}
