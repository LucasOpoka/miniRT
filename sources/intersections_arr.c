/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_arr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:58:10 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/01 19:33:13 by lopoka           ###   ########.fr       */
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
	t_intersection	*new;

	if (!xs->arr || xs->i < xs->size - 1)
		return ;
	new = malloc((xs->size + xs->to_add) * sizeof(t_intersection));
	if (!new)
		return (ft_free_xs(xs));
	ft_memmove(new, xs->arr, xs->size * sizeof(t_intersection));
	free(xs->arr);
	xs->arr = new;
	xs->size += xs->to_add;
}

void	ft_add_intersection(t_xs *xs, t_obj *obj, double t)
{
	t_intersection	*intr;

	ft_xs_realloc(xs);
	if (!xs->arr)
		return ;
	intr = &xs->arr[xs->i];
	intr->obj = obj;
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
