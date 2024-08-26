/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:54:43 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/26 17:17:22 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_COLOUR_H
# define GET_COLOUR_H

t_clr	ft_get_color(const t_ray *ray, t_scene *scene,
		int recursion_depth, t_intersects *intersect);

#endif
