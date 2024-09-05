/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lopoka@student.hive.fi>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:40:23 by lucas             #+#    #+#             */
/*   Updated: 2024/09/05 17:51:43 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

void	uninit_mlx(t_mrt *mrt)
{
	if (mrt->img)
		mlx_delete_image(mrt->mlx, mrt->img);
	if (mrt->mlx)
		mlx_close_window(mrt->mlx);
}

void	init_mlx(t_mrt *mrt)
{
	mrt->mlx = NULL;
	mrt->img = NULL;
	mrt->mlx = mlx_init(CANV_WDTH, CANV_HGHT, "miniRT", true);
	if (!mrt->mlx)
		uninit_mlx(mrt);
	mrt->img = mlx_new_image(mrt->mlx, CANV_WDTH, CANV_HGHT);
	if (!mrt->img || mlx_image_to_window(mrt->mlx, mrt->img, 0, 0) < 0)
		uninit_mlx(mrt);
}
