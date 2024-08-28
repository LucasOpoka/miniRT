/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtrx_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 09:57:29 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/23 13:48:31 by lucas            ###   ########.fr       */
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
// https://byjus.com/maths/cofactor/
double	ft_mtrx4_cfc(const t_mtrx4 *mtrx4, int row, int col)
{
	t_mtrx3	mtrx3;

	ft_mtrx4_sub(&mtrx3, mtrx4, row, col);
	if ((row + col) % 2)
		return (-ft_mtrx3_det(&mtrx3));
	return (ft_mtrx3_det(&mtrx3));
}

// Get determinant of a 4x4 matrix
// https://www.cuemath.com/algebra/determinant-of-matrix/
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


// Get cofactor of 3x3 matrix at row and col
// https://byjus.com/maths/cofactor/
double	ft_mtrx3_cfc(const t_mtrx3 *mtrx3, int row, int col)
{
	t_mtrx2	mtrx2;

	ft_mtrx3_sub(&mtrx2, mtrx3, row, col);
	if ((row + col) % 2)
		return (-ft_mtrx2_det(&mtrx2));
	return (ft_mtrx2_det(&mtrx2));
}

// Get determinant of a 3x3 matrix
// https://www.cuemath.com/algebra/determinant-of-matrix/
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
// https://www.cuemath.com/algebra/inverse-of-a-matrix/
void	ft_mtrx4_inv(t_mtrx4 *res, const t_mtrx4 *mtrx4)
{
	double	det;
	int		r;
	int		c;

	r = 0;
	det = ft_mtrx4_det(mtrx4);
	if (fabs(det) < 0.001)
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

void	ft_vct_mtrx_mult(t_vct *res, const t_mtrx4 *m, const t_vct *v)
{
	res->x = v->x * m[0][0][0] + v->y * m[0][0][1] + v->z * m[0][0][2] + v->w * m[0][0][3];
	res->y = v->x * m[0][1][0] + v->y * m[0][1][1] + v->z * m[0][1][2] + v->w * m[0][1][3];
	res->z = v->x * m[0][2][0] + v->y * m[0][2][1] + v->z * m[0][2][2] + v->w * m[0][2][3];
	res->w = v->x * m[0][3][0] + v->y * m[0][3][1] + v->z * m[0][3][2] + v->w * m[0][3][3];
}


// Multiply two matrices
// https://www.mathsisfun.com/algebra/matrix-multiplying.html
void	ft_mtrx_mtrx_mult(t_mtrx4 *res, const t_mtrx4 *a, const t_mtrx4 *b)
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
