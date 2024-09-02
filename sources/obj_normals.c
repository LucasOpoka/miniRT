/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_normals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lopoka@student.hive.fi>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:17:04 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/02 17:46:14 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

void	ft_sphere_normal_and_color(t_comps *comps)
{
	t_obj	*obj;
	t_vct	*world_point;
	t_vct	obj_point;

	obj = comps->obj;
	world_point = &comps->point;
	ft_vct_mtrx_mult(&obj_point, &obj->world_to_obj, world_point);
	ft_vct_mtrx_mult(&comps->normal, &obj->normal_to_world, &obj_point);
	comps->normal.w = 0;
	ft_vct_norm(&comps->normal);
	comps->color = obj->color;
}

void	ft_plane_normal_and_color(t_comps *comps)
{
	t_obj	*obj;
	t_vct	obj_normal;
	t_vct	obj_point;	

	obj = comps->obj;
	ft_bzero(&obj_normal, sizeof(t_vct));
	obj_normal.y = 1;
	ft_vct_mtrx_mult(&comps->normal, &obj->normal_to_world, &obj_normal);
	comps->normal.w = 0;
	ft_vct_norm(&comps->normal);
	ft_vct_mtrx_mult(&obj_point, &obj->world_to_obj, &comps->point);
	if ((int)(floor(obj_point.x) + floor(obj_point.z)) % 2 == 0)
		comps->color = ft_create_clr(255, 255, 255);
	else
		comps->color = comps->obj->color;
}

void	ft_cylinder_normal_and_color(t_comps *comps)
{
	t_obj	*obj;
	t_vct	obj_point;
	t_vct	obj_normal;
	double	dist;

	obj = comps->obj;
	ft_vct_mtrx_mult(&obj_point, &obj->world_to_obj, &comps->point);
	obj_point.w = 0;
	dist = obj_point.x * obj_point.x + obj_point.z * obj_point.z;
	ft_bzero(&obj_normal, sizeof(t_vct));
	if (dist < 1 && (obj_point.y >= obj->height / 2 - EPSILON))
		obj_normal.y = 1;
	else if (dist < 1 && (obj_point.y <= -obj->height / 2 + EPSILON))
		obj_normal.y = -1;
	else
	{
		obj_normal.x = obj_point.x;
		obj_normal.z = obj_point.z;
		ft_vct_norm(&obj_normal);
	}
	ft_vct_mtrx_mult(&comps->normal, &obj->normal_to_world, &obj_normal);
	comps->normal.w = 0;
	ft_vct_norm(&comps->normal);
	comps->color = obj->color;
}

void	ft_get_obj_normal_and_color(t_comps *comps)
{
	if (comps->obj->type == t_sphere)
		return (ft_sphere_normal_and_color(comps));
	if (comps->obj->type == t_plane)
		return (ft_plane_normal_and_color(comps));
	if (comps->obj->type == t_cylinder)
		return (ft_cylinder_normal_and_color(comps));
}
