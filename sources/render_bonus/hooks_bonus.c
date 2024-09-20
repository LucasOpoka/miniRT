/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:14:55 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/20 17:23:07 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/miniRT.h"
#include <pthread.h>

void		render_image(t_mrt *mrt);

void		threads_wait(t_mrt *mrt);
void		threads_join(t_mrt *mrt);
void		uninit_mlx(t_mrt *mrt);

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
	printf("threads joined\n");
}

static int	move_cam_key(mlx_key_data_t k, t_cam *cam)
{
	if (k.key == MLX_KEY_A)
		cam->pos.x -= MOVE_SIZE;
	else if (k.key == MLX_KEY_D)
		cam->pos.x += MOVE_SIZE;
	else if (k.key == MLX_KEY_W)
		cam->pos.z += MOVE_SIZE;
	else if (k.key == MLX_KEY_S)
		cam->pos.z -= MOVE_SIZE;
	else if (k.key == MLX_KEY_SPACE)
		cam->pos.y += MOVE_SIZE;
	else if (k.key == MLX_KEY_LEFT_SHIFT)
		cam->pos.y -= MOVE_SIZE;
	else
		return (0);
	return (1);
}

static void	move_camera(mlx_key_data_t k, t_mrt *mrt, t_scene *scene)
{
	if (k.action != MLX_PRESS)
		return ;
	if (!move_cam_key(k, &scene->cam))
		return ;
	ft_init_cam(&scene->cam);
	ft_set_cam_matrices(&scene->cam);
	render_image(mrt);
}

void	key_hook(mlx_key_data_t k, void *vd)
{
	t_mrt	*mrt;
	t_scene	*scene;

	mrt = (t_mrt *)vd;
	scene = mrt->scene;
	if (k.key == MLX_KEY_ESCAPE && k.action == MLX_PRESS)
		close_hook(mrt);
	move_camera(k, mrt, scene);
}
