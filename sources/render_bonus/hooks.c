/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:14:55 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/18 19:23:49 by atorma           ###   ########.fr       */
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

static void	move_camera(mlx_key_data_t k, t_mrt *mrt, t_scene *scene)
{
	if (k.action != MLX_PRESS)
		return ;
	if (k.key == MLX_KEY_A)
		scene->cam.pos.x -= 0.1f;
	else if (k.key == MLX_KEY_D)
		scene->cam.pos.x += 0.1f;
	else if (k.key == MLX_KEY_W)
		scene->cam.pos.y += 0.1f;
	else if (k.key == MLX_KEY_S)
		scene->cam.pos.y -= 0.1f;
	else if (k.key == MLX_KEY_F)
		scene->cam.pos.z += 0.1f;
	else if (k.key == MLX_KEY_B)
		scene->cam.pos.z -= 0.1f;
	else
		return ;
	ft_init_cam(&scene->cam);
	ft_set_cam_matrices(&scene->cam);
	render_image(mrt);
}

void	ft_keyboard_hooks(mlx_key_data_t k, void *vd)
{
	t_mrt	*mrt;
	t_scene	*scene;

	mrt = (t_mrt *)vd;
	scene = mrt->scene;
	if (k.key == MLX_KEY_ESCAPE && k.action == MLX_PRESS)
		close_hook(mrt);
	move_camera(k, mrt, scene);
}
