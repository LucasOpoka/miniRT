/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:16:20 by lucas             #+#    #+#             */
/*   Updated: 2024/08/18 13:48:02 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CAMERA_H
# define CAMERA_H

void	ft_init_camera(t_camera *camera);
void	ft_set_camera_matrices(t_camera *camera);
void	ft_set_world_to_camera(t_mtrx4 *world_to_camera, t_vct cam_position, t_vct cam_y_axis, t_vct cam_z_axis);

#endif
