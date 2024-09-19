/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:29:51 by atorma            #+#    #+#             */
/*   Updated: 2024/09/19 18:52:10 by atorma           ###   ########.fr       */
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

void	worker_render(t_scene *scene, t_worker *worker, t_block *block)
{
	t_ray	ray;
	t_clr	color;
	uint32_t	y;
	uint32_t	x;

	y = block->offset;
	while (y < (block->height + block->offset))
	{
		x = 0;
		while (x < block->width)
		{
			ft_pixel_to_ray(&ray, x, y, &scene->cam);
			color = ft_final_color(&ray, scene, 5, &worker->xs);
			mlx_put_pixel(worker->mrt->img, x++, y, ft_clr_to_int(color));
		}
		y++;
	}
}

void	*worker_routine(void *ptr)
{
	t_worker	*worker = (t_worker *)ptr;
	mlx_image_t	*img;
	t_block		block;
	uint32_t	i;

	worker = (t_worker *)ptr;
	img = worker->mrt->img;
	while (worker_wait(worker))
	{
		i = worker->index;
		block.count = img->height / BLOCK_SIZE;
		block.height = BLOCK_SIZE;
		block.width = img->width;
		while (i < block.count)
		{
			block.offset = i * block.height;
			if (i == block.count - 1)
				block.height += img->height % block.height;
			worker_render(worker->scene, worker, &block);
			i += THREAD_COUNT;
		}
		worker_signal_finish(worker);
	}
	return (NULL);
}
