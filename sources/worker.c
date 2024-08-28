/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:29:51 by atorma            #+#    #+#             */
/*   Updated: 2024/08/28 18:10:30 by atorma           ###   ########.fr       */
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
	worker->intersects.size = 256;
	worker->intersects.arr = malloc(worker->intersects.size * sizeof(t_intersection));
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
	worker->block_count = mrt->img->height / BLOCK_SIZE;
	worker->block_size = BLOCK_SIZE;
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
	t_intersects *inter = &worker->intersects;

	int start_y = i * worker->block_size;
	if (i == worker->block_count - 1)
		worker->block_size += worker->mrt->img->height % BLOCK_SIZE;

	int y = start_y;
	while (y < (start_y + worker->block_size))
	{
		int x = 0;
		while (x < CANV_WDTH)
		{
			ft_pixel_to_ray(&ray, x, y, &scene->camera);
			//bvh_intersect(ray, scene, 0, inter);
			bvh_intersect_ordered(ray, scene, inter);
			//ft_get_intersections(ray, scene, inter);
			color = ft_get_color(&ray, scene, 3, inter);
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
		worker_wait(worker);
		while (i < worker->block_count)
		{
			worker_render_section(worker, worker->scene, i);
			i += MAX_THREADS;
		}
		worker_signal_finish(worker);	
	}

	free(ptr);
	return (NULL);
}
