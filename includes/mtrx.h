/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtrx.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:16:04 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/21 19:28:48 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MTRX_H
# define MTRX_H

double	ft_mtrx2_det(const t_mtrx2 *mtrx2);

double	ft_mtrx4_cfc(const t_mtrx4 *mtrx4, int row, int col);
double	ft_mtrx4_det(const t_mtrx4 *mtrx4);
void	ft_mtrx4_inv(t_mtrx4 *res, const t_mtrx4 *mtrx4);

void	ft_mtrx3_sub(t_mtrx2 *mtrx2, const t_mtrx3 *mtrx3, int row, int col);
double	ft_mtrx3_cfc(const t_mtrx3 *mtrx3, int row, int col);
double	ft_mtrx3_det(const t_mtrx3 *mtrx3);

void	ft_vct_x_mtrx(t_vct *res, const t_mtrx4 *m, const t_vct *v);
void	ft_mtrx_x_mtrx(t_mtrx4 *res, const t_mtrx4 *a, const t_mtrx4 *b);

void	ft_set_trnsl_mtrx(t_mtrx4 *mtrx4, double x, double y, double z);
void	ft_set_identity_mtrx(t_mtrx4 *mtrx4);
void	ft_set_scaling_mtrx(t_mtrx4 *mtrx4, double x, double y, double z);
void	ft_mtrx4_transpose(t_mtrx4 *out, const t_mtrx4 *in);

#endif
