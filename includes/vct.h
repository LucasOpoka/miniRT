/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:02:34 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/17 14:22:07 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef VCT_H
# define VCT_H

t_vct	ft_create_vct(float x, float y, float z);
float	ft_vct_dot(t_vct a, t_vct b);
t_vct	ft_vct_sclr_mult(t_vct a, float b);
t_vct	ft_vct_sclr_div(t_vct a, float b);
t_vct	ft_vct_neg(t_vct a);
t_vct	ft_vct_sub(t_vct a, t_vct b);
t_vct	ft_vct_add(t_vct a, t_vct b);
float	ft_vct_len(t_vct a);
void	ft_vct_scale(t_vct *res, t_vct *a, float scale);
void	ft_vct_norm(t_vct *a);
void	ft_vct_cross_prod(t_vct *res, t_vct a, t_vct b);

#endif
