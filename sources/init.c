/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lopoka@student.hive.fi>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:40:23 by lucas             #+#    #+#             */
/*   Updated: 2024/08/04 15:47:17 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

void	ft_init_stc(t_mrt *mrt)
{
	mrt->mlx = NULL;
	mrt->img = NULL;
	mrt->mlx = mlx_init(CANV_WDTH, CANV_HGHT, "miniRT", true);
	if (!mrt->mlx)
		ft_close(mrt);
	mrt->img = mlx_new_image(mrt->mlx, CANV_WDTH, CANV_HGHT);
	if (!mrt->img || mlx_image_to_window(mrt->mlx, mrt->img, 0, 0) < 0)
		ft_close(mrt);
}
