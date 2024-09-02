/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_transforms.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:43:29 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/02 19:37:17 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SHAPES_H
# define SHAPES_H

void	ft_set_all_objs_matrices(t_scene *scene);
void	ft_set_obj_matrices(t_obj *obj);
void	ft_set_rot_mtrx(t_mtrx4 *rot_mtrx, t_obj *obj);
void	ft_rot_mtrx_sub(t_mtrx4 *rot_mtrx, t_vct r_ax, double r_angle);
void	ft_set_rot_around_x(t_mtrx4 *rot_mtrx, double rot_angle);
void	ft_combine_obj_transforms(t_obj *obj, t_mtrx4 *scaling_mtrx, t_mtrx4 *rot_mtrx, t_mtrx4 *trnsl_mtrx);

# endif
