/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clr_math.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:06:41 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/03 18:00:33 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CLR_MATH_H
# define CLR_MATH_H

t_clr		ft_create_clr(double r, double g, double b);
t_clr		ft_clr_add(t_clr a, t_clr b);
t_clr		ft_clr_scl(t_clr clr, double x);
t_clr		ft_clr_x_clr(t_clr a, t_clr b);
double		ft_clip_color(double clr);
uint32_t	ft_clr_to_int(t_clr clr);
uint32_t	ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a);

#endif
