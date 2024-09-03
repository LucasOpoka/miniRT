/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_comps.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:37:22 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/03 16:46:31 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PREP_COMPS_H
# define PREP_COMPS_H

void	ft_prep_comps(t_comps *comps, t_intrsc *hit, t_ray *ray, t_xs *xs);
t_vct	ft_ray_point(const t_ray *ray, double t);
t_vct	ft_reflect(const t_vct *in, const t_vct *normal);
t_vct	ft_over_point(const t_vct *point, const t_vct *normal);
t_vct	ft_under_point(const t_vct *point, const t_vct *normal);
void	ft_get_refr_ind(t_comps *comps, t_xs *xs, t_intrsc *hit);
void	ft_set_refr_ind(double *n, t_xs *containers);
int		ft_containers_include(t_xs *containers, t_obj *obj);
void	ft_remove_container(t_xs *containers, t_intrsc *curr);
void	ft_get_schlick(t_comps *comps);

#endif
