/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_transforms.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:43:29 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/26 16:23:06 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SHAPES_H
# define SHAPES_H

void	ft_set_all_shapes_matrices(t_scene *scene);
void	ft_set_shape_matrices(t_shape *shape);
void	ft_set_rotation_mtrx(t_mtrx4 *rotation_mtrx, t_shape *shape);
void	ft_rotation_mtrx_from_axis_and_angle(t_mtrx4 *rotation_mtrx, t_vct r_ax, float r_angle);
void	ft_set_rotation_around_x(t_mtrx4 *rotation_mtrx, float rot_angle);
void	ft_combine_shape_transforms(t_shape *shape, t_mtrx4 *scaling_mtrx, t_mtrx4 *rotation_mtrx, t_mtrx4 *translation_mtrx);

# endif
