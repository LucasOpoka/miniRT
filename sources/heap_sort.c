/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:44:46 by atorma            #+#    #+#             */
/*   Updated: 2024/09/07 16:55:57 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	compare_xs(t_intrsc *a, t_intrsc *b)
{
	const double	t_a = a->t;
	const double	t_b = b->t;

	return ((t_a > t_b) - (t_a < t_b));
}

static void	swap_inter(t_intrsc *arr, int i, int j)
{
	unsigned char	tmp[sizeof(t_intrsc)];
	const uint32_t	size = sizeof(t_intrsc);

	ft_memcpy(tmp, arr + i, size);
	ft_memcpy(arr + i, arr + j, size);
	ft_memcpy(arr + j, tmp, size);
}

static void	heapify(t_intrsc *arr, int n, int i)
{
	const int	left = 2 * i + 1;
	const int	right = 2 * i + 2;
	int			max;

	max = i;
	if (left < n && compare_xs(arr + left, arr + max) > 0)
		max = left;
	if (right < n && compare_xs(arr + right, arr + max) > 0)
		max = right;
	if (max != i)
	{
		swap_inter(arr, i, max);
		heapify(arr, n, max);
	}
}

/*
 * Recursive heap sort for intersections
 */

void	heap_sort_xs(t_xs *xs)
{
	const int	n = xs->i;
	int			i;

	if (xs->arr == NULL || xs->i <= 1)
		return ;
	i = n / 2 - 1;
	while (i >= 0)
	{
		heapify(xs->arr, n, i);
		i--;
	}
	i = n - 1;
	while (i > 0)
	{
		swap_inter(xs->arr, 0, i);
		heapify(xs->arr, i, 0);
		i--;
	}
}
