/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:13:02 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/03 18:33:47 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHONG_H
# define PHONG_H

t_clr	ft_phong(t_comps *comps, t_scene *scene, t_light *light);
t_clr	ft_ambient(t_ambient *ambient, t_clr *obj_color);
t_clr	ft_diffuse(t_phong *ph, t_comps *comps, t_light *light);
t_clr	ft_specular(t_phong *ph, t_comps *comps, t_light *light);
int		ft_shadow(t_scene *scene, t_light *light, t_vct *over_point);

#endif
