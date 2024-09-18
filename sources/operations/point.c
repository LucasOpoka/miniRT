/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:45:19 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/18 17:52:29 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/miniRT.h"

t_vct	ft_create_point(double x, double y, double z)
{
	t_vct	point;

	point.x = x;
	point.y = y;
	point.z = z;
	point.w = 1;
	return (point);
}
