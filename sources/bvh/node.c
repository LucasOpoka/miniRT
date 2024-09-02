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

double	node_cost(t_node *node)
{
	double	ext[3];
	double	area;

	ext[0] = node->bounds.max[0] - node->bounds.min[0];
	ext[1] = node->bounds.max[1] - node->bounds.min[1];
	ext[2] = node->bounds.max[2] - node->bounds.min[2];
	area = ext[0] * ext[1] + ext[1] * ext[2] + ext[2] * ext[0];
	return (node->count * area);
}
