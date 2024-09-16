/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_normals.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:18:28 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/16 19:24:04 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SHAPES_NORMALS_H
# define SHAPES_NORMALS_H

void	ft_get_obj_normal_and_color(t_comps *comps);
void	ft_sphere_normal_and_color(t_comps *comps);
void	ft_plane_normal_and_color(t_comps *comps);
void	ft_cylinder_normal_and_color(t_comps *comps);
void	ft_triangle_normal_and_color(t_comps *comps);
void	ft_cone_normal_and_color(t_comps *comps);

#endif
