/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_normal_and_color1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lopoka@student.hive.fi>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:17:04 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/20 17:04:38 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/miniRT.h"

void	ft_get_obj_normal_and_color(t_comps *comps)
{
	if (comps->obj->type == t_sphere)
		return (ft_sphere_normal_and_color(comps));
	if (comps->obj->type == t_plane)
		return (ft_plane_normal_and_color(comps));
	if (comps->obj->type == t_cylinder)
		return (ft_cylinder_normal_and_color(comps));
	if (comps->obj->type == t_triangle)
		return (ft_triangle_normal_and_color(comps));
	if (comps->obj->type == t_cone)
		return (ft_cone_normal_and_color(comps));
}
