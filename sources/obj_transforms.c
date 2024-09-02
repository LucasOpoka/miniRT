/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_transforms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:44:06 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/02 17:15:23 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

void	ft_set_all_objs_matrices(t_scene *scene)
{
	size_t	i;
	t_obj	*obj;

	i = 0;
	while (i < scene->objs.i)
	{
		obj = (t_obj *) scene->objs.arr[i++];
		ft_set_obj_matrices(obj);
	}
}

// The transforms are applied in order: scaling, rotation, trnsl
void	ft_set_obj_matrices(t_obj *obj)
{
	t_mtrx4	scaling_mtrx;
	t_mtrx4	rotation_mtrx;
	t_mtrx4	trnsl_mtrx;

	ft_set_scaling_mtrx(&scaling_mtrx, obj->scale.x, obj->scale.y, obj->scale.z);
	ft_set_rotation_mtrx(&rotation_mtrx, obj);
	ft_set_trnsl_mtrx(&trnsl_mtrx, obj->pos.x, obj->pos.y, obj->pos.z);
	ft_combine_obj_transforms(obj, &scaling_mtrx, &rotation_mtrx, &trnsl_mtrx);
}

int	ft_is_zero_vct(t_vct a)
{
	if (fabs(a.x) < EPSILON && fabs(a.y) < EPSILON && fabs(a.z) < EPSILON)
		return (1);
	return (0);
}

void	ft_set_rotation_mtrx(t_mtrx4 *rotation_mtrx, t_obj *obj)
{
	t_vct	y_axis;
	t_vct	rotation_axis;
	double	rotation_angle;

	if (ft_is_zero_vct(obj->orientation))
		return (ft_set_identity_mtrx(rotation_mtrx));
	ft_bzero(&y_axis, sizeof(t_vct));
	y_axis.y = 1;
	ft_vct_norm(&y_axis);
	ft_vct_norm(&obj->orientation);
	ft_vct_cross_prod(&rotation_axis, &y_axis, &obj->orientation);
	ft_vct_norm(&rotation_axis);
	rotation_angle = acos(ft_vct_dot(&obj->orientation, &y_axis));
	ft_rotation_mtrx_from_axis_and_angle(rotation_mtrx, rotation_axis, rotation_angle);
}

// Set rotation matrix of an object
// https://en.wikipedia.org/wiki/Rotation_matrix
void	ft_rotation_mtrx_from_axis_and_angle(t_mtrx4 *rotation_mtrx, t_vct r_ax, double r_angle)
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

// The Raytracer Challenge p.54 The matrices need to be multiplied in the
// reverse order that the one in which we want them applied
void	ft_combine_obj_transforms(t_obj *obj, t_mtrx4 *scaling_mtrx, t_mtrx4 *rotation_mtrx, t_mtrx4 *trnsl_mtrx)
{
	t_mtrx4	trnsl_x_rot;

	ft_mtrx_mtrx_mult(&trnsl_x_rot, trnsl_mtrx, rotation_mtrx);
	ft_mtrx_mtrx_mult(&obj->obj_to_world, &trnsl_x_rot, scaling_mtrx);
	ft_mtrx4_inv(&obj->world_to_obj, &obj->obj_to_world);
	ft_mtrx4_transpose(&obj->normal_to_world, &obj->world_to_obj);
}
