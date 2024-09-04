/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:29:51 by atorma            #+#    #+#             */
/*   Updated: 2024/09/04 11:05:17 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"
#include "../includes/bvh.h"
#include <pthread.h>

long long	time_ms(void);

t_worker	*worker_init(t_mrt *mrt, t_scene *scene, int i)
{
	t_worker	*worker;

	worker = ft_calloc(1, (sizeof(t_worker)));
	if (!worker)
		return (0);
	worker->mrt = mrt;
	worker->scene = scene;
	worker->index = i;
	ft_init_xs(&worker->xs);
	return (worker);
}

int	worker_wait(t_worker *worker)
{
	int exit_status = 0;
	t_mrt	*mrt;

	mrt = worker->mrt;
	pthread_mutex_lock(&mrt->lock);
	while (!mrt->exit && worker->done && mrt->do_render)
		pthread_cond_wait(&mrt->notify, &mrt->lock);
	while (!mrt->exit && !mrt->do_render)
		pthread_cond_wait(&mrt->notify, &mrt->lock);
	exit_status = mrt->exit;
	pthread_mutex_unlock(&mrt->lock);
	if (exit_status)
	{
		printf("worker %d, exiting...\n", worker->index);
		return (0);
	}
	worker->done = 0;
	worker->block_count = mrt->img->height / BLOCK_SIZE;
	worker->block_size = BLOCK_SIZE;
	return (1);
}

void	worker_signal_finish(t_worker *worker)
{
	t_mrt	*mrt;

	mrt = worker->mrt;
	pthread_mutex_lock(&mrt->lock);
	mrt->threads_finished++;
	pthread_cond_signal(&mrt->complete);
	pthread_mutex_unlock(&mrt->lock);
	worker->done = 1;
}

void	worker_render_section(t_worker *worker, t_scene *scene, int i)
{
	t_ray		ray;
	t_clr		color;
	t_xs		*xs = &worker->xs;

	int start_y = i * worker->block_size;
	if (i == worker->block_count - 1)
		worker->block_size += worker->mrt->img->height % BLOCK_SIZE;

	int y = start_y;
	while (y < (start_y + worker->block_size))
	{
		int x = 0;
		while (x < CANV_WDTH)
		{
			xs->i = 0;
			ft_pixel_to_ray(&ray, x, y, &scene->cam);
			bvh_intersect(ray, scene, xs);
			color = ft_final_color(&ray, scene, 5, xs);
			mlx_put_pixel(worker->mrt->img, x, y, ft_clr_to_int(color));
			x++;
		}
		y++;
	}
}

void	*worker_routine(void *ptr)
{
	t_worker	*worker;

	worker = (t_worker *)ptr;
	int	i;

	while (1)
	{
		i = worker->index;
		if (!worker_wait(worker))
			break ;
		while (i < worker->block_count)
		{
			worker_render_section(worker, worker->scene, i);
			i += MAX_THREADS;
		}
		worker_signal_finish(worker);	
	}
	ft_free_xs(&worker->xs);
	free(ptr);
	return (NULL);
}
