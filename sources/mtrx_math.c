/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtrx_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 09:57:29 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/17 19:57:03 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

// Create a 2x2 matrix by removing row and column from the passed 3x3 matrix
void	ft_mtrx3_sub(t_mtrx2 *mtrx2, t_mtrx3 *mtrx3, int row, int col)
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
void	ft_mtrx4_sub(t_mtrx3 *mtrx3, t_mtrx4 *mtrx4, int row, int col)
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

float	ft_mtrx2_det(t_mtrx2 *mtrx2)
{
	return (mtrx2[0][0][0] * mtrx2[0][1][1] - mtrx2[0][0][1] * mtrx2[0][1][0]);
}

// Get cofactor of 4x4 matrix at row and col
// https://byjus.com/maths/cofactor/
float	ft_mtrx4_cfc(t_mtrx4 *mtrx4, int row, int col)
{
	t_mtrx3	mtrx3;

	ft_mtrx4_sub(&mtrx3, mtrx4, row, col);
	if ((row + col) % 2)
		return (-ft_mtrx3_det(&mtrx3));
	return (ft_mtrx3_det(&mtrx3));
}

// Get determinant of a 4x4 matrix
// https://www.cuemath.com/algebra/determinant-of-matrix/
float	ft_mtrx4_det(t_mtrx4 *mtrx4)
{
	int		col;
	float	res;

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
float	ft_mtrx3_cfc(t_mtrx3 *mtrx3, int row, int col)
{
	t_mtrx2	mtrx2;

	ft_mtrx3_sub(&mtrx2, mtrx3, row, col);
	if ((row + col) % 2)
		return (-ft_mtrx2_det(&mtrx2));
	return (ft_mtrx2_det(&mtrx2));
}

// Get determinant of a 3x3 matrix
// https://www.cuemath.com/algebra/determinant-of-matrix/
float	ft_mtrx3_det(t_mtrx3 *mtrx3)
{
	int		col;
	float	res;

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
void	ft_mtrx4_inv(t_mtrx4 *res, t_mtrx4 *mtrx4)
{
	float	det;
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

void	ft_vct_mtrx_mult(t_vct *res, t_mtrx4 m, t_vct v)
{
	res->x = v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2] + v.w * m[0][3];
	res->y = v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2] + v.w * m[1][3];
	res->z = v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2] + v.w * m[2][3];
	res->w = v.x * m[3][0] + v.y * m[3][1] + v.z * m[3][2] + v.w * m[3][3];
}


// Multiply two matrices
// https://www.mathsisfun.com/algebra/matrix-multiplying.html
void	ft_mtrx_mtrx_mult(t_mtrx4 *res, t_mtrx4 a, t_mtrx4 b)
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
				res[0][row][col] += a[row][common] * b[common][col];
				common++;
			}
			col++;
		}
		row++;
	}
}

/*
int main(void)
{
	t_mtrx4 big;
	t_mtrx3 small;
	t_mtrx2	smallest;
	t_mtrx4 biginv;

	int 	num = 0;

	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			big[i][j] = (num++ % 10);
			if (i == 3 && j == 3)
				big[i][j] = 7;
			printf("%d", (int)big[i][j]);
		}
		printf("\n");
	}

	ft_mtrx4_sub(&small, &big, 0,0);

	for (int i=0; i<3; i++)
	{
		for (int j=0; j<3; j++)
		{
			printf("%d", (int)small[i][j]);
		}
		printf("\n");
	}

	ft_mtrx3_sub(&smallest, &small, 0,0);

	for (int i=0; i<2; i++)
	{
		for (int j=0; j<2; j++)
		{
			printf("%d", (int)smallest[i][j]);
		}
		printf("\n");
	}

	printf("4x4 determinant %f\n", ft_mtrx4_det(&big));
	printf("3x3 determinant %f\n", ft_mtrx3_det(&small));
	printf("2x2 determinant %f\n", ft_mtrx2_det(&smallest));

	ft_mtrx4_inv(&biginv, &big);
	
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
			printf("%f\t", biginv[i][j]);
		printf("\n");
	}

	t_mtrx4 big_res;

	printf("\n");
	ft_mtrx_mtrx_mult(&big_res, big, big);
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
			printf("%f\t", big_res[i][j]);
		printf("\n");
	}

}*/
