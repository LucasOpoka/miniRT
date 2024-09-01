/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:54:43 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/01 18:52:35 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_COLOR_H
# define GET_COLOR_H

t_clr	ft_get_color(const t_ray *ray, t_scene *scene, int recursion_depth,
			t_xs *xs);

#endif
