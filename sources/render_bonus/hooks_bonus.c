/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:14:55 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/26 22:46:05 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/miniRT.h"
#include <pthread.h>

void	threads_wait(t_mrt *mrt);
void	threads_join(t_mrt *mrt);
void	uninit_mlx(t_mrt *mrt);
void	move_camera(mlx_key_data_t k, t_mrt *mrt, t_scene *scene);

void	close_hook(void *ptr)
{
	t_mrt	*mrt;

	mrt = ptr;
	if (!mrt->thread_count)
		return ;
	threads_wait(mrt);
	pthread_mutex_lock(&mrt->lock);
	mrt->exit = 1;
	pthread_cond_broadcast(&mrt->notify);
	pthread_mutex_unlock(&mrt->lock);
	threads_join(mrt);
	uninit_mlx(mrt);
}

void	key_hook(mlx_key_data_t k, void *vd)
{
	t_mrt	*mrt;
	t_scene	*scene;

	if (k.action != MLX_PRESS)
		return ;
	mrt = (t_mrt *)vd;
	scene = mrt->scene;
	if (k.key == MLX_KEY_ESCAPE)
		close_hook(mrt);
	else
		move_camera(k, mrt, scene);
}
