/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:02:34 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/05 15:48:13 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef VCT_H
# define VCT_H

t_vct	ft_create_vct(double x, double y, double z);
t_vct	ft_create_point(double x, double y, double z);
double	ft_vct_dot(const t_vct *a, const t_vct *b);
double	ft_vct_dot2(const t_vct *a, const t_vct *b);
t_vct	ft_vct_x_sclr(const t_vct *a, double b);
t_vct	ft_vct_sclr_div(const t_vct *a, double b);
t_vct	ft_vct_neg(const t_vct *a);
t_vct	ft_vct_sub(const t_vct *a, const t_vct *b);
t_vct	ft_vct_add(const t_vct *a, const t_vct *b);
double	ft_vct_len(const t_vct *a);
void	ft_vct_scale(t_vct *res, const t_vct *a, double scale);
void	ft_vct_norm(t_vct *a);
void	ft_vct_cross_prod(t_vct *res, const t_vct *a, const t_vct *b);

#endif
