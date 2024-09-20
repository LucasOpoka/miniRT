/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_normal_and_color2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lopoka@student.hive.fi>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:17:04 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/20 17:04:55 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/miniRT.h"

void	ft_sphere_normal_and_color(t_comps *comps)
{
	t_obj	*obj;
	t_vct	*world_point;
	t_vct	obj_point;

	obj = comps->obj;
	world_point = &comps->point;
	ft_vct_x_mtrx(&obj_point, &obj->world_to_obj, world_point);
	ft_vct_x_mtrx(&comps->normal, &obj->normal_to_world, &obj_point);
	comps->normal.w = 0;
	ft_vct_norm(&comps->normal);
	comps->color = obj->color;
	ft_texture_and_bump(comps, obj, obj_point);
}

void	ft_plane_normal_and_color(t_comps *comps)
{
	t_obj	*obj;
	t_vct	obj_normal;
	t_vct	obj_point;	

	obj = comps->obj;
	obj_normal = ft_create_vct(0, 1, 0);
	ft_vct_x_mtrx(&comps->normal, &obj->normal_to_world, &obj_normal);
	comps->normal.w = 0;
	ft_vct_norm(&comps->normal);
	ft_vct_x_mtrx(&obj_point, &obj->world_to_obj, &comps->point);
	ft_texture_and_bump(comps, obj, obj_point);
}

void	ft_cylinder_normal_and_color(t_comps *comps)
{
	t_obj	*obj;
	t_vct	obj_point;
	t_vct	obj_normal;
	double	dist;

	obj = comps->obj;
	ft_vct_x_mtrx(&obj_point, &obj->world_to_obj, &comps->point);
	obj_point.w = 1;
	dist = sqrt(pow(obj_point.x, 2) + pow(obj_point.z, 2));
	obj_normal = ft_create_vct(0, 0, 0);
	if (dist < 1 && (obj_point.y >= 0.5 - EPSILON))
		obj_normal.y = 1;
	else if (dist < 1 && (obj_point.y <= -0.5 + EPSILON))
		obj_normal.y = -1;
	else
	{
		obj_normal.x = obj_point.x;
		obj_normal.z = obj_point.z;
		ft_vct_norm(&obj_normal);
	}
	ft_vct_x_mtrx(&comps->normal, &obj->normal_to_world, &obj_normal);
	comps->normal.w = 0;
	ft_vct_norm(&comps->normal);
	comps->color = obj->color;
	ft_texture_and_bump(comps, obj, obj_point);
}

void	ft_triangle_normal_and_color(t_comps *comps)
{
	t_obj	*obj;
	t_vct	obj_point;

	obj = comps->obj;
	comps->normal = obj->normal;
	comps->color = obj->color;
	ft_vct_x_mtrx(&obj_point, &obj->world_to_obj, &comps->point);
	obj_point.w = 1;
	ft_texture_and_bump(comps, obj, obj_point);
}

void	ft_cone_normal_and_color(t_comps *comps)
{
	t_obj	*obj;
	t_vct	obj_point;
	t_vct	obj_normal;
	double	dist;

	obj = comps->obj;
	ft_vct_x_mtrx(&obj_point, &obj->world_to_obj, &comps->point);
	obj_point.w = 1;
	dist = sqrt(pow(obj_point.x, 2) + pow(obj_point.z, 2));
	if (dist < fabs(obj_point.y) && obj_point.y >= 1 - EPSILON)
		obj_normal = ft_create_vct(0, 1, 0);
	else if (dist < fabs(obj_point.y) && obj_point.y <= EPSILON)
		obj_normal = ft_create_vct(0, -1, 0);
	else
	{
		obj_normal = ft_create_vct(obj_point.x, dist, obj_point.z);
		if (obj_point.y > 0)
			obj_normal.y *= -1;
		ft_vct_norm(&obj_normal);
	}
	ft_vct_x_mtrx(&comps->normal, &obj->normal_to_world, &obj_normal);
	comps->normal.w = 0;
	ft_vct_norm(&comps->normal);
	comps->color = obj->color;
	ft_texture_and_bump(comps, obj, obj_point);
}
