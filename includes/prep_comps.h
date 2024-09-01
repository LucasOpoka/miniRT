/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_comps.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:37:22 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/01 14:39:35 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PREP_COMPS_H
# define PREP_COMPS_H

void	ft_prepare_computations(t_comps *comps, t_intersection *closest, const t_ray *ray, t_xs *xs);
void	ft_prepare_computations2(t_comps *comps, t_intersection *closest, const t_ray *ray, t_xs *xs);
t_vct	ft_ray_point(const t_ray *ray, double t);
t_vct	ft_reflect(const t_vct *in, const t_vct *normal);
t_vct	ft_over_point(const t_vct *point, const t_vct *normal);

#endif
