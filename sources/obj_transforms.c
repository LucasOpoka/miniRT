/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_transforms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:44:06 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/02 19:47:13 by lopoka           ###   ########.fr       */
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

// The transforms are applied in order: scaling, rot, trnsl
void	ft_set_obj_matrices(t_obj *obj)
{
	t_mtrx4	scl_mtrx;
	t_mtrx4	rot_mtrx;
	t_mtrx4	trnsl_mtrx;

	ft_set_scaling_mtrx(&scl_mtrx, obj->scale.x, obj->scale.y, obj->scale.z);
	ft_set_rot_mtrx(&rot_mtrx, obj);
	ft_set_trnsl_mtrx(&trnsl_mtrx, obj->pos.x, obj->pos.y, obj->pos.z);
	ft_combine_obj_transforms(obj, &scl_mtrx, &rot_mtrx, &trnsl_mtrx);
}

void	ft_set_rot_mtrx(t_mtrx4 *rot_mtrx, t_obj *obj)
{
	t_vct	y_axis;
	t_vct	rot_axis;
	double	rot_angle;

	if (ft_vct_len(&obj->orientation) < EPSILON)
		return (ft_set_identity_mtrx(rot_mtrx));
	ft_bzero(&y_axis, sizeof(t_vct));
	y_axis.y = 1;
	ft_vct_norm(&y_axis);
	ft_vct_norm(&obj->orientation);
	ft_vct_cross_prod(&rot_axis, &y_axis, &obj->orientation);
	ft_vct_norm(&rot_axis);
	rot_angle = acos(ft_vct_dot(&obj->orientation, &y_axis));
	ft_rot_mtrx_sub(rot_mtrx, rot_axis, rot_angle);
}

// Set rotation matrix of an object
// https://en.wikipedia.org/wiki/Rotation_matrix
void	ft_rot_mtrx_sub(t_mtrx4 *rot_mtrx, t_vct r_ax, double r_angle)
{
	double	cs;
	double	sn;
	double	one_min_cs;

	cs = cos(r_angle);
	sn = sin(r_angle);
	one_min_cs = 1 - cs;
	ft_bzero(rot_mtrx, sizeof(t_mtrx4));
	rot_mtrx[0][0][0] = r_ax.x * r_ax.x * one_min_cs + cs;
	rot_mtrx[0][0][1] = r_ax.x * r_ax.y * one_min_cs - r_ax.z * sn;
	rot_mtrx[0][0][2] = r_ax.x * r_ax.z * one_min_cs + r_ax.y * sn;
	rot_mtrx[0][1][0] = r_ax.x * r_ax.y * one_min_cs + r_ax.z * sn;
	rot_mtrx[0][1][1] = r_ax.y * r_ax.y * one_min_cs + cs;
	rot_mtrx[0][1][2] = r_ax.y * r_ax.z * one_min_cs - r_ax.x * sn;
	rot_mtrx[0][2][0] = r_ax.x * r_ax.z * one_min_cs - r_ax.y * sn;
	rot_mtrx[0][2][1] = r_ax.y * r_ax.z * one_min_cs + r_ax.x * sn;
	rot_mtrx[0][2][2] = r_ax.z * r_ax.z * one_min_cs + cs;
	rot_mtrx[0][3][3] = 1;
}

// The Raytracer Challenge p.54 The matrices need to be multiplied in the
// reverse order that the one in which we want them applied
void	ft_combine_obj_transforms(t_obj *obj, t_mtrx4 *scl_mtrx,
		t_mtrx4 *rot_mtrx, t_mtrx4 *trnsl_mtrx)
{
	t_mtrx4	trnsl_x_rot;

	ft_mtrx_mtrx_mult(&trnsl_x_rot, trnsl_mtrx, rot_mtrx);
	ft_mtrx_mtrx_mult(&obj->obj_to_world, &trnsl_x_rot, scl_mtrx);
	ft_mtrx4_inv(&obj->world_to_obj, &obj->obj_to_world);
	ft_mtrx4_transpose(&obj->normal_to_world, &obj->world_to_obj);
}
