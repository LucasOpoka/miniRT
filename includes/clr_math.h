/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clr_math.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:06:41 by lucas             #+#    #+#             */
/*   Updated: 2024/08/26 16:07:34 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CLR_MTH_H
# define CLR_MTH_H

t_clr		ft_create_clr(float r, float g, float b);
t_clr		ft_clr_add(t_clr a, t_clr b);
t_clr		ft_clr_sclr_mult(t_clr clr, float x);
t_clr		ft_clr_clr_mult(t_clr a, t_clr b);
float		ft_clip_color(float clr);
uint32_t	ft_clr_to_int(t_clr clr);
uint32_t 	ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a);

#endif
