/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:16:20 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/21 19:35:31 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CAMERA_H
# define CAMERA_H

void	ft_init_cam(t_cam *cam);
void	ft_set_cam_matrices(t_cam *cam);
void	ft_world_to_cam(t_mtrx4 *world_to_cam, t_vct *cam_pos, t_vct *cam_up,
			t_vct *cam_dir);
void	ft_pixel_to_ray(t_ray *world_ray, double x, double y, t_cam *cam);

#endif
