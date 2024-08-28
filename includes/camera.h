/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:16:20 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/28 15:37:03 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CAMERA_H
# define CAMERA_H

void	ft_init_camera(t_camera *camera);
void	ft_set_camera_matrices(t_camera *camera);
void	ft_set_world_to_camera(t_mtrx4 *world_to_camera, const t_vct *cam_position, t_vct *cam_y_axis, const t_vct *cam_z_axis);
void	ft_pixel_to_ray(t_ray *world_ray, double pixel_x, double pixel_y, t_camera *camera);

#endif
