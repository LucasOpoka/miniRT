/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_arr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:58:10 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/18 17:53:03 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/miniRT.h"

int	ft_init_xs(t_xs *xs)
{
	xs->size = 200;
	xs->to_add = 100;
	xs->i = 0;
	xs->arr = (t_intrsc *) malloc(xs->size * sizeof(t_intrsc));
	return (xs->arr != NULL);
}

int	ft_xs_realloc(t_xs *xs)
{
	t_intrsc	*new;

	if (!xs->arr)
		return (0);
	if (xs->i < xs->size - 1)
		return (1);
	new = malloc((xs->size + xs->to_add) * sizeof(t_intrsc));
	if (!new)
	{
		ft_free_xs(xs);
		return (0);
	}
	ft_memmove(new, xs->arr, xs->size * sizeof(t_intrsc));
	free(xs->arr);
	xs->arr = new;
	xs->size += xs->to_add;
	return (1);
}

int	ft_add_intersection(t_xs *xs, t_obj *obj, double t)
{
	t_intrsc	*intr;

	if (!ft_xs_realloc(xs))
		return (0);
	intr = &xs->arr[xs->i];
	intr->obj = obj;
	intr->t = t;
	xs->i++;
	return (1);
}

void	ft_free_xs(t_xs *xs)
{
	if (!xs->arr)
		return ;
	free(xs->arr);
	xs->arr = 0;
}
