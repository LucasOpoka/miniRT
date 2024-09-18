/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:22:57 by atorma            #+#    #+#             */
/*   Updated: 2024/09/18 19:22:58 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	ft_init_cam(t_cam *cam)
{
	double	fov_distance;
	double	aspect_ratio;

	fov_distance = tan(cam->fov * 0.5 * M_PI / 180);
	aspect_ratio = CANV_WDTH / CANV_HGHT;
	cam->half_wdth = fov_distance * aspect_ratio;
	cam->half_hght = fov_distance;
	if (MAYA_STYLE)
	{
		cam->half_wdth = fov_distance;
		cam->half_hght = fov_distance / aspect_ratio;
	}
	cam->pixel_size = 2 * cam->half_wdth / CANV_WDTH;
}

void	ft_set_cam_matrices(t_cam *cam)
{
	t_vct	cam_up;

	cam_up = ft_create_vct(0, 1, 0);
	ft_vct_norm(&cam->dir);
	ft_world_to_cam(&cam->world_to_cam, &cam->pos, &cam_up, &cam->dir);
	ft_mtrx4_inv(&cam->cam_to_world, &cam->world_to_cam);
}

void	ft_world_to_cam(t_mtrx4 *world_to_cam, t_vct *cam_pos, t_vct *cam_up,
			t_vct *cam_dir)
{
	t_vct		cam_left;
	t_vct		cam_true_up;
	t_mtrx4		rot_matrix;
	t_mtrx4		trnsl_matrix;

	ft_vct_norm(cam_up);
	ft_vct_cross_prod(&cam_left, cam_dir, cam_up);
	if (ft_vct_len(&cam_left) < EPSILON)
		cam_left = ft_create_vct(-1, 0, 0);
	ft_vct_norm(&cam_left);
	ft_vct_cross_prod(&cam_true_up, &cam_left, cam_dir);
	ft_vct_norm(&cam_true_up);
	ft_bzero(&rot_matrix, sizeof(t_mtrx4));
	rot_matrix[0][0] = cam_left.x;
	rot_matrix[0][1] = cam_left.y;
	rot_matrix[0][2] = cam_left.z;
	rot_matrix[1][0] = cam_true_up.x;
	rot_matrix[1][1] = cam_true_up.y;
	rot_matrix[1][2] = cam_true_up.z;
	rot_matrix[2][0] = -cam_dir->x;
	rot_matrix[2][1] = -cam_dir->y;
	rot_matrix[2][2] = -cam_dir->z;
	rot_matrix[3][3] = 1;
	ft_set_trnsl_mtrx(&trnsl_matrix, -cam_pos->x, -cam_pos->y, -cam_pos->z);
	ft_mtrx_x_mtrx(world_to_cam, &rot_matrix, &trnsl_matrix);
}

void	ft_pixel_to_ray(t_ray *world_ray, double x, double y, t_cam *cam)
{
	t_ray	cam_ray;
	t_vct	pixel_world;

	cam_ray.d.x = cam->half_wdth - (x + 0.5) * cam->pixel_size;
	cam_ray.d.y = cam->half_hght - (y + 0.5) * cam->pixel_size;
	cam_ray.d.z = -1;
	cam_ray.d.w = 1;
	ft_bzero(&cam_ray.o, sizeof(t_vct));
	cam_ray.o.w = 1;
	ft_vct_x_mtrx(&world_ray->o, &cam->cam_to_world, &cam_ray.o);
	ft_vct_x_mtrx(&pixel_world, &cam->cam_to_world, &cam_ray.d);
	world_ray->d = ft_vct_sub(&pixel_world, &world_ray->o);
	world_ray->d.w = 0;
	ft_vct_norm(&world_ray->d);
}
