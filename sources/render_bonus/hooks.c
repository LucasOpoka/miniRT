/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:14:55 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/18 18:39:27 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/miniRT.h"
#include <pthread.h>

void	render_image(t_mrt *mrt);

void	threads_wait(t_mrt *mrt);
void	threads_join(t_mrt *mrt);
void	uninit_mlx(t_mrt *mrt);

void	close_hook(void *ptr)
{
	t_mrt	*mrt;

	mrt = ptr;
	threads_wait(mrt);
	pthread_mutex_lock(&mrt->lock);
	mrt->exit = 1;
	pthread_cond_broadcast(&mrt->notify);
	printf("threads notified...\n");
	pthread_mutex_unlock(&mrt->lock);
	uninit_mlx(mrt);
	threads_join(mrt);
	printf("threads joined\n");
}

void	ft_keyboard_hooks(mlx_key_data_t k, void *vd)
{
	t_mrt	*mrt;
	t_scene	*scene;

	mrt = (t_mrt *)vd;
	scene = mrt->scene;
	if (k.key == MLX_KEY_ESCAPE && k.action == MLX_PRESS)
		close_hook(mrt);
	if (k.action == MLX_PRESS)
	{
		if (k.key == MLX_KEY_A)
			scene->cam.pos.x -= 0.1f;
		else if (k.key == MLX_KEY_D)
			scene->cam.pos.x += 0.1f;
		else if (k.key == MLX_KEY_W)
			scene->cam.pos.y += 0.1f;
		else if (k.key == MLX_KEY_S)
			scene->cam.pos.y -= 0.1f;
		else
			return ;
		ft_init_cam(&scene->cam);
		ft_set_cam_matrices(&scene->cam);
		ft_set_all_objs_matrices(scene);
		render_image(mrt);
	}
	if (k.key == MLX_KEY_C && k.action == MLX_PRESS)
		render_image(mrt);
}
