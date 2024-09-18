/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:29:51 by atorma            #+#    #+#             */
/*   Updated: 2024/09/19 01:28:50 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/bvh.h"
#include "../../includes/miniRT.h"
#include <pthread.h>

long long	time_ms(void);

int	worker_init(t_mrt *mrt, t_scene *scene, t_worker *worker, int i)
{
	worker->mrt = mrt;
	worker->scene = scene;
	worker->index = i;
	return (ft_init_xs(&worker->xs));
}

int	worker_wait(t_worker *worker)
{
	int		exit_status;
	t_mrt	*mrt;

	exit_status = 0;
	mrt = worker->mrt;
	pthread_mutex_lock(&mrt->lock);
	while (!mrt->exit && worker->done && mrt->threads_finished > 0)
		pthread_cond_wait(&mrt->notify, &mrt->lock);
	while (!mrt->do_render && !mrt->exit)
		pthread_cond_wait(&mrt->notify, &mrt->lock);
	exit_status = mrt->exit;
	pthread_mutex_unlock(&mrt->lock);
	worker->done = 0;
	worker->block_count = mrt->img->height / BLOCK_SIZE;
	worker->block_size = BLOCK_SIZE;
	return (exit_status == 0);
}

void	worker_signal_finish(t_worker *worker)
{
	t_mrt	*mrt;

	worker->done = 1;
	mrt = worker->mrt;
	pthread_mutex_lock(&mrt->lock);
	mrt->threads_finished++;
	pthread_cond_signal(&mrt->complete);
	pthread_mutex_unlock(&mrt->lock);
}

void	worker_render_section(t_worker *worker, t_scene *scene, uint32_t i)
{
	t_ray	ray;
	t_clr	color;
	uint32_t	start_y;
	uint32_t	y;
	uint32_t	x;

	start_y = i * worker->block_size;
	if (i == worker->block_count - 1)
		worker->block_size += worker->mrt->img->height % BLOCK_SIZE;
	y = start_y;
	while (y < (start_y + worker->block_size))
	{
		x = 0;
		while (x < worker->mrt->img->width)
		{
			ft_pixel_to_ray(&ray, x, y, &scene->cam);
			color = ft_final_color(&ray, scene, 5, &worker->xs);
			mlx_put_pixel(worker->mrt->img, x, y, ft_clr_to_int(color));
			x++;
		}
		y++;
	}
}

void	*worker_routine(void *ptr)
{
	t_worker	*worker;
	uint32_t		    i;

	worker = (t_worker *)ptr;
	while (worker_wait(worker))
	{
		i = worker->index;
		while (i < worker->block_count)
		{
			worker_render_section(worker, worker->scene, i);
			i += THREAD_COUNT;
		}
		worker_signal_finish(worker);
	}
	return (NULL);
}
