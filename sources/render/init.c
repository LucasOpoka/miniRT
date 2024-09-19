/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lopoka@student.hive.fi>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:40:23 by lucas             #+#    #+#             */
/*   Updated: 2024/09/19 20:04:47 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/miniRT.h"

void		close_hook(void *ptr);
void		key_hook(mlx_key_data_t k, void *vd);

void	uninit_mlx(t_mrt *mrt)
{
	if (mrt->img)
		mlx_delete_image(mrt->mlx, mrt->img);
	if (mrt->mlx)
		mlx_close_window(mrt->mlx);
}

static int	init_mlx(t_mrt *mrt)
{
	mrt->mlx = NULL;
	mrt->img = NULL;
	mrt->mlx = mlx_init(CANV_WDTH, CANV_HGHT, "miniRT", true);
	if (!mrt->mlx)
		return (0);
	mrt->img = mlx_new_image(mrt->mlx, CANV_WDTH, CANV_HGHT);
	if (!mrt->img || mlx_image_to_window(mrt->mlx, mrt->img, 0, 0) < 0)
	{
		uninit_mlx(mrt);
		return (0);
	}
	mlx_close_hook(mrt->mlx, &close_hook, mrt);
	mlx_key_hook(mrt->mlx, &key_hook, mrt);
	return (1);
}

int	init_minirt(t_mrt *mrt, t_scene *scene)
{
	if (!init_mlx(mrt))
	{
		printf("Error: MLX42 initialization failed\n");
		return (0);
	}
	scene->bvh.root = bvh_build(scene);
	if (!scene->bvh.root)
	{
		printf("Error: occured during BVH building\n");
		return (0);
	}
	return (1);
}
