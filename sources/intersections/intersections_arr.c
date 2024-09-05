/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_arr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:58:10 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/03 11:10:38 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

void	ft_init_xs(t_xs *xs)
{
	xs->size = 200;
	xs->to_add = 100;
	xs->i = 0;
	xs->arr = (t_intrsc *) malloc(xs->size * sizeof(t_intrsc));
}

void	ft_xs_realloc(t_xs *xs)
{
	t_intrsc	*new;

	if (!xs->arr || xs->i < xs->size - 1)
		return ;
	new = malloc((xs->size + xs->to_add) * sizeof(t_intrsc));
	if (!new)
		return (ft_free_xs(xs));
	ft_memmove(new, xs->arr, xs->size * sizeof(t_intrsc));
	free(xs->arr);
	xs->arr = new;
	xs->size += xs->to_add;
}

void	ft_add_intersection(t_xs *xs, t_obj *obj, double t)
{
	t_intrsc	*intr;

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
