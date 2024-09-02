/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:52:24 by atorma            #+#    #+#             */
/*   Updated: 2024/08/31 17:18:50 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <math.h>

void	node_min_max(double *to_min, double *to_max, double *min, double *max)
{
	to_min[0] = fminf(to_min[0], min[0]);
	to_min[1] = fminf(to_min[1], min[1]);
	to_min[2] = fminf(to_min[2], min[2]);

	to_max[0] = fmaxf(to_max[0], max[0]);
	to_max[1] = fmaxf(to_max[1], max[1]);
	to_max[2] = fmaxf(to_max[2], max[2]);
}

double	node_cost(t_node *node)
{
	double	extent[3];
	double	area;

	extent[0] = node->max[0] - node->min[0];
	extent[1] = node->max[1] - node->min[1];
	extent[2] = node->max[2] - node->min[2];
	area = extent[0] * extent[1] + extent[1] * extent[2] + extent[2] * extent[0];
	return (node->count * area);
}
