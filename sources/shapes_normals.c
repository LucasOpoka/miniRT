/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_normals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:17:04 by lucas             #+#    #+#             */
/*   Updated: 2024/08/30 18:13:51 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

void	ft_sphere_normal_and_color(t_comps *comps)
{
	t_shape	*shape = comps->shape;
	t_vct	*world_point = &comps->point;
	t_vct	shape_point;
	t_vct	world_normal;
	
	ft_vct_mtrx_mult(&shape_point, &shape->world_to_shape, world_point);
	ft_vct_mtrx_mult(&world_normal, &shape->normal_to_world, &shape_point);	
	world_normal.w = 0;
	ft_vct_norm(&world_normal);
	comps->normal = world_normal;
	comps->color = comps->shape->color;
}

void	ft_plane_normal_and_color(t_comps *comps)
{
	t_shape *shape = comps->shape;
	t_vct	shape_normal;
	t_vct	world_normal;

	ft_bzero(&shape_normal, sizeof(t_vct));
	shape_normal.y = 1;
	ft_vct_mtrx_mult(&world_normal, &shape->normal_to_world, &shape_normal);
	world_normal.w = 0;
	ft_vct_norm(&world_normal);
	comps->normal = world_normal;

	t_vct	shape_point;	
	ft_vct_mtrx_mult(&shape_point, &shape->world_to_shape, &comps->point);

	if ( (int) (floor(shape_point.x) + floor(shape_point.z)) % 2 == 0)
		comps->color = ft_create_clr(255,255,255);
	else
	comps->color = comps->shape->color;

}

void	ft_cylinder_normal_and_color(t_comps *comps)
{
	t_shape	*shape = comps->shape;
	t_vct	*world_point = &comps->point;
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
	comps->normal = world_normal;
	comps->color = comps->shape->color;
}

void	ft_get_shape_normal_and_color(t_comps *comps)
{
	if (comps->shape->type == t_sphere)
		return (ft_sphere_normal_and_color(comps));
	if (comps->shape->type == t_plane)
		return (ft_plane_normal_and_color(comps));
	if (comps->shape->type == t_cylinder)
		return (ft_cylinder_normal_and_color(comps));
	// To-do: add other shapes

}
