/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:54:43 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/24 17:10:35 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef COLOUR_H
# define COLOUR_H

t_clr		ft_get_color(const t_ray *ray, t_scene *scene, int recursion_depth, t_void_arr *intersections);
t_clr		ft_light(t_clr color, t_scene *scene, t_vct P, t_vct N, t_vct V, float s);
uint32_t 	ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
t_clr		ft_create_clr(float r, float g, float b);
float		ft_modify_channel(float ch, float i);
uint32_t	ft_clr_to_int(t_clr clr);
t_vct		ft_reflect_ray(t_vct R, t_vct N);

#endif
