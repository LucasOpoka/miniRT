/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:29:51 by atorma            #+#    #+#             */
/*   Updated: 2024/08/24 18:56:06 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"
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
	return (worker);
}

void	worker_wait(t_worker *worker)
{
	t_mrt	*mrt;

	mrt = worker->mrt;
	pthread_mutex_lock(&mrt->lock);
	while (worker->done && mrt->do_render)
		pthread_cond_wait(&mrt->notify, &mrt->lock);
	while (!mrt->do_render)
		pthread_cond_wait(&mrt->notify, &mrt->lock);
	pthread_mutex_unlock(&mrt->lock);
	worker->done = 0;
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
	t_ray		world_ray;
	t_clr		color;
	int			block_count = CANV_HGHT / BLOCK_SIZE;
	int			block_size = BLOCK_SIZE;

	int start_y = i * block_size;
	if (i == block_count - 1)
		block_size += CANV_HGHT % BLOCK_SIZE;

	int y = start_y;
	while (y < (start_y + block_size))
	{
		int x = 0;
		while (x < CANV_WDTH)
		{
			ft_init_void_arr(&worker->intersections);
			ft_pixel_to_ray(&world_ray, x, y, &scene->camera);
			ft_get_intersections(world_ray, scene, &worker->intersections);
			color = ft_get_color(&world_ray, scene, 3, &worker->intersections);
			mlx_put_pixel(worker->mrt->img, x, y, ft_clr_to_int(color));
			ft_free_void_arr(&worker->intersections);
			x++;
		}
		y++;
	}
}

void	*worker_routine(void *ptr)
{
	t_worker	*worker;

	worker = (t_worker *)ptr;
	int			block_count = CANV_HGHT / BLOCK_SIZE;
	int	i;

	while (1)
	{
		i = worker->index;
		worker_wait(worker);
		while (i < block_count)
		{
			worker_render_section(worker, worker->scene, i);
			i += MAX_THREADS;
		}
		worker_signal_finish(worker);	
	}

	free(ptr);
	return (NULL);
}
