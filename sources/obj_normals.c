/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_normals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lopoka@student.hive.fi>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:17:04 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/07 22:27:31 by lopoka           ###   ########.fr       */
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
	ft_vct_x_mtrx(&obj_point, &obj->world_to_obj, world_point);
	ft_vct_x_mtrx(&comps->normal, &obj->normal_to_world, &obj_point);
	comps->normal.w = 0;
	ft_vct_norm(&comps->normal);
	// TEST
	double	uv[2];
	ft_spherical_map(uv, &obj_point);
	uv[1] = 1 - uv[1];
	double x = uv[0] * (obj->ppm->width - 1);
	double y = uv[1] * (obj->ppm->height - 1);
	int xx = (int) round(x);
	int yy = (int) round(y);
	comps->color = obj->ppm->colors[yy][xx];
	//comps->color = ft_checkers(uv, 16, 8);
	//comps->color = obj->color;
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
	double	uv[2];
	ft_planar_map(uv, &obj_point);
	comps->color = ft_checkers(uv, 2, 2);
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
	if (dist < obj->radius && (obj_point.y >= obj->height / 2 - EPSILON))
		obj_normal.y = 1;
	else if (dist < obj->radius && (obj_point.y <= -obj->height / 2 + EPSILON))
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
}

void	ft_triangle_normal_and_color(t_comps *comps)
{
	t_obj	*obj;

	obj = comps->obj;
	comps->normal = obj->normal;
	comps->color = obj->color;
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
	obj_normal = ft_create_vct(0, 0, 0);
	if (dist < fabs(obj_point.y) && obj_point.y >= 1 - EPSILON)
		obj_normal.y = 1;
	else if (dist < fabs(obj_point.y) && obj_point.y <= EPSILON)
		obj_normal.y = -1;
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
}

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
