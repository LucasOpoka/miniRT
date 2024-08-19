/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:54:43 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/19 17:04:30 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef COLOUR_H
# define COLOUR_H

t_clr		ft_get_color(t_vct O, t_vct D, t_scene *scene, float t_min, float t_max, int recursion_depth, float t_closest, t_shape *shape_closest);
t_clr		ft_light(t_clr color, t_scene *scene, t_vct P, t_vct N, t_vct V, float s);
uint32_t 	ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
t_clr		ft_create_clr(float r, float g, float b);
float		ft_modify_channel(float ch, float i);
uint32_t	ft_clr_to_int(t_clr clr);
t_vct		ft_reflect_ray(t_vct R, t_vct N);

#endif
