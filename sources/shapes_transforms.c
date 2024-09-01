/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_transforms.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:44:06 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/26 16:14:26 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

void	ft_set_all_shapes_matrices(t_scene *scene)
{
	size_t	i;
	t_shape	*shape;

	i = 0;
	while (i < scene->shapes.i)
	{
		shape = (t_shape *) scene->shapes.arr[i++];
		ft_set_shape_matrices(shape);
	}
}

// The transforms are applied in order: scaling, rotation, translation
void	ft_set_shape_matrices(t_shape *shape)
{
	t_mtrx4	scaling_mtrx;
	t_mtrx4	rotation_mtrx;
	t_mtrx4	translation_mtrx;

	ft_set_scaling_mtrx(&scaling_mtrx, shape->scale.x, shape->scale.y, shape->scale.z);
	ft_set_rotation_mtrx(&rotation_mtrx, shape);
	ft_set_translation_mtrx(&translation_mtrx, shape->position.x, shape->position.y, shape->position.z);
	ft_combine_shape_transforms(shape, &scaling_mtrx, &rotation_mtrx, &translation_mtrx);
}

int	ft_is_zero_vct(t_vct a)
{
	if (fabs(a.x) < EPSILON && fabs(a.y) < EPSILON && fabs(a.z) < EPSILON)
		return (1);
	return (0);
}

void	ft_set_rotation_mtrx(t_mtrx4 *rotation_mtrx, t_shape *shape)
{
	t_vct	y_axis;
	t_vct	rotation_axis;
	double	rotation_angle;

	if (ft_is_zero_vct(shape->orientation))
		return (ft_set_identity_mtrx(rotation_mtrx));
	ft_bzero(&y_axis, sizeof(t_vct));
	y_axis.y = 1;
	ft_vct_norm(&y_axis);
	ft_vct_norm(&shape->orientation);
	ft_vct_cross_prod(&rotation_axis, &y_axis, &shape->orientation);
	ft_vct_norm(&rotation_axis);
	rotation_angle = acos(ft_vct_dot(&shape->orientation, &y_axis));
	ft_rotation_mtrx_from_axis_and_angle(rotation_mtrx, rotation_axis, rotation_angle);
}

// Set rotation matrix of an object
// https://en.wikipedia.org/wiki/Rotation_matrix
void ft_rotation_mtrx_from_axis_and_angle(t_mtrx4 *rotation_mtrx, t_vct r_ax, double r_angle)
{
	double	cs;
	double	sn;
	double	one_min_cs;

	cs = cos(r_angle);
	sn = sin(r_angle);
	one_min_cs = 1 - cs;
	ft_bzero(rotation_mtrx, sizeof(t_mtrx4));
	rotation_mtrx[0][0][0] = r_ax.x * r_ax.x * one_min_cs + cs;
	rotation_mtrx[0][0][1] = r_ax.x * r_ax.y * one_min_cs - r_ax.z * sn;
	rotation_mtrx[0][0][2] = r_ax.x * r_ax.z * one_min_cs + r_ax.y * sn;
	rotation_mtrx[0][1][0] = r_ax.x * r_ax.y * one_min_cs + r_ax.z * sn;
	rotation_mtrx[0][1][1] = r_ax.y * r_ax.y * one_min_cs + cs;
	rotation_mtrx[0][1][2] = r_ax.y * r_ax.z * one_min_cs - r_ax.x * sn;
	rotation_mtrx[0][2][0] = r_ax.x * r_ax.z * one_min_cs - r_ax.y * sn;
	rotation_mtrx[0][2][1] = r_ax.y * r_ax.z * one_min_cs + r_ax.x * sn;
	rotation_mtrx[0][2][2] = r_ax.z * r_ax.z * one_min_cs + cs;
	rotation_mtrx[0][3][3] = 1;
}

// The Raytracer Challenge p.54 The matrices need to be multiplied in the reverse order that the one in which we want them applied
// https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/geometry/transforming-normals.html
void	ft_combine_shape_transforms(t_shape *shape, t_mtrx4 *scaling_mtrx, t_mtrx4 *rotation_mtrx, t_mtrx4 *translation_mtrx)
{
	t_mtrx4	trnsl_x_rot;

	ft_mtrx_mtrx_mult(&trnsl_x_rot, translation_mtrx, rotation_mtrx);
	ft_mtrx_mtrx_mult(&shape->shape_to_world, &trnsl_x_rot, scaling_mtrx);
	ft_mtrx4_inv(&shape->world_to_shape, &shape->shape_to_world);
	ft_mtrx4_transpose(&shape->normal_to_world, &shape->world_to_shape);
}
