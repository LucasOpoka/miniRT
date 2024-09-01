/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:03:58 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/01 18:53:21 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef INTERSECTIONS_H
# define INTERSECTIONS_H

void			ft_get_intersections(t_ray world_ray, t_scene *scene, t_xs *xs);
t_intersection	*ft_closest_intersection(t_xs *xs);

#endif
