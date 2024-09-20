/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:54:43 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/20 15:51:45 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_COLOR_H
# define GET_COLOR_H

t_clr	ft_final_color(t_ray *ray, t_scene *scene, int recur_lmt, t_xs *xs);
t_clr	ft_refraction(t_clr_recur rec);
t_clr	ft_reflection(t_clr_recur rec);
t_clr	ft_light_color(t_clr_recur rec);

#endif
