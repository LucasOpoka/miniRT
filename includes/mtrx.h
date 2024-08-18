/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtrx.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:16:04 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/18 14:26:18 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MTRX_H
# define MTRX_H

float	ft_mtrx2_det(t_mtrx2 *mtrx2);

float	ft_mtrx4_cfc(t_mtrx4 *mtrx4, int row, int col);
float	ft_mtrx4_det(t_mtrx4 *mtrx4);
void	ft_mtrx4_inv(t_mtrx4 *res, t_mtrx4 *mtrx4);

float	ft_mtrx3_cfc(t_mtrx3 *mtrx3, int row, int col);
float	ft_mtrx3_det(t_mtrx3 *mtrx3);

void	ft_vct_mtrx_mult(t_vct *res, t_mtrx4 mtrx4, t_vct vct);
void	ft_mtrx_mtrx_mult(t_mtrx4 *res, t_mtrx4 a, t_mtrx4 b);

void	ft_translation_mtrx(t_mtrx4 *mtrx4, float x, float y, float z);

#endif
