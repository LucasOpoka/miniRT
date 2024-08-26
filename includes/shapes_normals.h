/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_normals.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:18:28 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/26 16:20:08 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SHAPES_NORMALS_H
# define SHAPES_NORMALS_H

t_vct	ft_shape_normal(const t_shape *shape, const t_vct *world_point);

t_vct	ft_sphere_normal(const t_shape *shape, const t_vct *world_point);

#endif
