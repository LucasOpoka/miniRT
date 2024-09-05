/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:03:58 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/05 11:18:22 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef INTERSECTIONS_H
# define INTERSECTIONS_H

void		ft_get_intrscs(t_ray world_ray, t_scene *scene, t_xs *xs);
t_intrsc	*ft_hit(t_xs *xs);

// Cylinder functions
void		ft_cylinder_intersection(t_ray ray, t_obj *obj, t_xs *xs);
void		ft_intersect_caps(t_ray ray, t_obj *obj, t_xs *xs);
int			ft_check_caps(t_ray ray, double t);
void		ft_swap_doubles(double *a, double *b);

#endif
