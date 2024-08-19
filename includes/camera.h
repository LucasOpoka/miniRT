/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:16:20 by lucas             #+#    #+#             */
/*   Updated: 2024/08/19 16:07:15 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CAMERA_H
# define CAMERA_H

void	ft_init_camera(t_camera *camera);
void	ft_set_camera_matrices(t_camera *camera);
void	ft_set_world_to_camera(t_mtrx4 *world_to_camera, t_vct cam_position, t_vct cam_y_axis, t_vct cam_z_axis);
t_vct	ft_pixel_to_ray(float pixel_x, float pixel_y, t_camera camera, t_vct *ray_origin_world);

#endif
