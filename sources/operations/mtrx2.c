/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtrx2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:32:43 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/18 17:51:44 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/miniRT.h"

// Get cofactor of 3x3 matrix at row and col
double	ft_mtrx3_cfc(const t_mtrx3 *mtrx3, int row, int col)
{
	t_mtrx2	mtrx2;

	ft_mtrx3_sub(&mtrx2, mtrx3, row, col);
	if ((row + col) % 2)
		return (-ft_mtrx2_det(&mtrx2));
	return (ft_mtrx2_det(&mtrx2));
}

// Get determinant of a 3x3 matrix
double	ft_mtrx3_det(const t_mtrx3 *mtrx3)
{
	int		col;
	double	res;

	col = 0;
	res = 0;
	while (col < 3)
	{
		res += ft_mtrx3_cfc(mtrx3, 0, col) * mtrx3[0][0][col];
		col++;
	}
	return (res);
}

// Get inverse of a matrix
void	ft_mtrx4_inv(t_mtrx4 *res, const t_mtrx4 *mtrx4)
{
	double	det;
	int		r;
	int		c;

	r = 0;
	det = ft_mtrx4_det(mtrx4);
	if (fabs(det) < EPSILON)
		return ;
	while (r < 4)
	{
		c = 0;
		while (c < 4)
		{
			res[0][c][r] = ft_mtrx4_cfc(mtrx4, r, c) / det;
			c++;
		}
		r++;
	}
}

void	ft_vct_x_mtrx(t_vct *res, const t_mtrx4 *m, const t_vct *v)
{
	res->x = v->x * m[0][0][0] + v->y * m[0][0][1]
		+ v->z * m[0][0][2] + v->w * m[0][0][3];
	res->y = v->x * m[0][1][0] + v->y * m[0][1][1]
		+ v->z * m[0][1][2] + v->w * m[0][1][3];
	res->z = v->x * m[0][2][0] + v->y * m[0][2][1]
		+ v->z * m[0][2][2] + v->w * m[0][2][3];
	res->w = v->x * m[0][3][0] + v->y * m[0][3][1]
		+ v->z * m[0][3][2] + v->w * m[0][3][3];
}

// Multiply two matrices
void	ft_mtrx_x_mtrx(t_mtrx4 *res, const t_mtrx4 *a, const t_mtrx4 *b)
{
	int	row;
	int	col;
	int	common;

	ft_bzero(res, sizeof(t_mtrx4));
	row = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			common = 0;
			while (common < 4)
			{
				res[0][row][col] += a[0][row][common] * b[0][common][col];
				common++;
			}
			col++;
		}
		row++;
	}
}
