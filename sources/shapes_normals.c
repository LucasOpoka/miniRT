/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_normals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:17:04 by lucas             #+#    #+#             */
/*   Updated: 2024/08/28 17:41:02 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

t_vct	ft_sphere_normal(const t_shape *shape, const t_vct *world_point)
{
	t_vct	shape_point;
	t_vct	world_normal;
	
	ft_vct_mtrx_mult(&shape_point, &shape->world_to_shape, world_point);
	ft_vct_mtrx_mult(&world_normal, &shape->normal_to_world, &shape_point);	
	world_normal.w = 0;
	ft_vct_norm(&world_normal);
	return (world_normal);
}

t_vct	ft_plane_normal(const t_shape *shape)
{
	t_vct	shape_normal;
	t_vct	world_normal;

	ft_bzero(&shape_normal, sizeof(t_vct));
	shape_normal.y = 1;
	ft_vct_mtrx_mult(&world_normal, &shape->normal_to_world, &shape_normal);
	world_normal.w = 0;
	ft_vct_norm(&world_normal);
	return (world_normal);	
}

t_vct	ft_cylinder_normal(const t_shape *shape, const t_vct *world_point)
{
	t_vct	shape_point;
	t_vct	shape_normal;
	t_vct	world_normal;
	double	dist;

	ft_vct_mtrx_mult(&shape_point, &shape->world_to_shape, world_point);
	shape_point.w = 0;
	dist = shape_point.x * shape_point.x + shape_point.z * shape_point.z;
	ft_bzero(&shape_normal, sizeof(t_vct));
	if (dist < 1 && (shape_point.y >= shape->height / 2 - EPSILON))
		shape_normal.y = 1;
	else if (dist < 1 && (shape_point.y <= -shape->height / 2 + EPSILON))
		shape_normal.y = -1;
	else
	{
		shape_normal.x = shape_point.x;
		shape_normal.z = shape_point.z;
		ft_vct_norm(&shape_normal);
	}
	ft_vct_mtrx_mult(&world_normal, &shape->normal_to_world, &shape_normal);
	world_normal.w = 0;
	ft_vct_norm(&world_normal);
	return (world_normal);
}

t_vct	ft_shape_normal(const t_shape *shape, const t_vct *world_point)
{
	if (shape->type == t_sphere)
		return (ft_sphere_normal(shape, world_point));
	if (shape->type == t_plane)
		return (ft_plane_normal(shape));
	if (shape->type == t_cylinder)
		return (ft_cylinder_normal(shape, world_point));
	// To-do: add other shapes

	return (ft_create_vct(12,13,14));
}
