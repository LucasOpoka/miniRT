/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtrx1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 09:57:29 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/02 17:04:56 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

// Create a 2x2 matrix by removing row and column from the passed 3x3 matrix
void	ft_mtrx3_sub(t_mtrx2 *mtrx2, const t_mtrx3 *mtrx3, int row, int col)
{
	int		r;
	int		c;
	int		r_sub;
	int		c_sub;

	r = 0;
	r_sub = 0;
	while (r < 3)
	{
		c = 0;
		c_sub = 0;
		while (c < 3)
		{
			if (r != row && c != col)
				mtrx2[0][r_sub][c_sub++] = mtrx3[0][r][c];
			c++;
		}
		r_sub += (r != row);
		r++;
	}
}

// Create a 3x3 matrix by removing row and column from the passed 4x4 matrix
void	ft_mtrx4_sub(t_mtrx3 *mtrx3, const t_mtrx4 *mtrx4, int row, int col)
{
	int		r;
	int		c;
	int		r_sub;
	int		c_sub;

	r = 0;
	r_sub = 0;
	while (r < 4)
	{
		c = 0;
		c_sub = 0;
		while (c < 4)
		{
			if (r != row && c != col)
				mtrx3[0][r_sub][c_sub++] = mtrx4[0][r][c];
			c++;
		}
		r_sub += (r != row);
		r++;
	}
}

double	ft_mtrx2_det(const t_mtrx2 *mtrx2)
{
	return (mtrx2[0][0][0] * mtrx2[0][1][1] - mtrx2[0][0][1] * mtrx2[0][1][0]);
}

// Get cofactor of 4x4 matrix at row and col
double	ft_mtrx4_cfc(const t_mtrx4 *mtrx4, int row, int col)
{
	t_mtrx3	mtrx3;

	ft_mtrx4_sub(&mtrx3, mtrx4, row, col);
	if ((row + col) % 2)
		return (-ft_mtrx3_det(&mtrx3));
	return (ft_mtrx3_det(&mtrx3));
}

// Get determinant of a 4x4 matrix
double	ft_mtrx4_det(const t_mtrx4 *mtrx4)
{
	int		col;
	double	res;

	col = 0;
	res = 0;
	while (col < 4)
	{
		res += ft_mtrx4_cfc(mtrx4, 0, col) * mtrx4[0][0][col];
		col++;
	}
	return (res);
}
