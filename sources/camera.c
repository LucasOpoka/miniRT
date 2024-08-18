/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:41:19 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/18 14:29:01 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

void	ft_init_camera(t_camera *camera)
{
	float fov_distance;
	float aspect_ratio;

	fov_distance = tan(camera->fov * 0.5 * M_PI / 180);
	aspect_ratio = CANV_WDTH / CANV_HGHT;
	camera->half_wdth = fov_distance * aspect_ratio;
	camera->half_hght = fov_distance;
	if (MAYA_STYLE)
	{
		camera->half_wdth = fov_distance;
		camera->half_hght = fov_distance / aspect_ratio;
	}
	camera->pixel_size = 2 * camera->half_wdth / CANV_WDTH;
}

void	ft_set_camera_matrices(t_camera *camera)
{
	t_vct	cam_y_axis;
	
	cam_y_axis.x = 0;
	cam_y_axis.y = 1;
	cam_y_axis.z = 0;
	cam_y_axis.w = 0;
	camera->direction.w = 1;
	ft_vct_norm(&camera->direction);
	ft_set_world_to_camera(&camera->world_to_camera, camera->position, cam_y_axis, camera->direction);
	ft_mtrx4_inv(&camera->camera_to_world, &camera->world_to_camera);
}

void	ft_set_world_to_camera(t_mtrx4 *world_to_camera, t_vct cam_position, t_vct cam_y_axis, t_vct cam_z_axis)
{
	t_vct		cam_x_axis;
	t_vct		cam_y_axis_negative;
	t_mtrx4		rotation_matrix;
	t_mtrx4		translation_matrix;

	ft_vct_norm(&cam_y_axis);
	ft_vct_cross_prod(&cam_x_axis, cam_z_axis, cam_y_axis);
	ft_vct_norm(&cam_x_axis);
	ft_vct_cross_prod(&cam_y_axis_negative, cam_x_axis, cam_z_axis);
	ft_vct_norm(&cam_y_axis_negative);
	ft_bzero(&rotation_matrix, sizeof(t_mtrx4));
	rotation_matrix[0][0] = cam_x_axis.x;
	rotation_matrix[0][1] = cam_x_axis.y;
	rotation_matrix[0][2] = cam_x_axis.z;
	rotation_matrix[1][0] = cam_y_axis_negative.x;
	rotation_matrix[1][1] = cam_y_axis_negative.y;
	rotation_matrix[1][2] = cam_y_axis_negative.z;
	rotation_matrix[2][0] = -cam_z_axis.x;
	rotation_matrix[2][1] = -cam_z_axis.y;
	rotation_matrix[2][2] = -cam_z_axis.z;
	rotation_matrix[3][3] = 1;
	ft_translation_mtrx(&translation_matrix, -cam_position.x, -cam_position.y, -cam_position.z);
	ft_mtrx_mtrx_mult(world_to_camera, rotation_matrix, translation_matrix);
}

