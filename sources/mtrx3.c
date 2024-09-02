/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtrx3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:03:01 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/02 17:03:21 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

void	ft_mtrx4_transpose(t_mtrx4 *out, const t_mtrx4 *in)
{
	int	r;
	int	c;

	r = 0;
	while (r < 4)
	{
		c = 0;
		while (c < 4)
		{
			out[0][r][c] = in[0][c][r];
			c++;
		}
		r++;
	}
}

void	ft_set_identity_mtrx(t_mtrx4 *mtrx4)
{
	ft_bzero(mtrx4, sizeof(t_mtrx4));
	mtrx4[0][0][0] = 1;
	mtrx4[0][1][1] = 1;
	mtrx4[0][2][2] = 1;
	mtrx4[0][3][3] = 1;
}

void	ft_set_trnsl_mtrx(t_mtrx4 *mtrx4, double x, double y, double z)
{
	ft_set_identity_mtrx(mtrx4);
	mtrx4[0][0][3] = x;
	mtrx4[0][1][3] = y;
	mtrx4[0][2][3] = z;
}

void	ft_set_scaling_mtrx(t_mtrx4 *mtrx4, double x, double y, double z)
{
	ft_bzero(mtrx4, sizeof(t_mtrx4));
	mtrx4[0][0][0] = x;
	mtrx4[0][1][1] = y;
	mtrx4[0][2][2] = z;
	mtrx4[0][3][3] = 1;
}
