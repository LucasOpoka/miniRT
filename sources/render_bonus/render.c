/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:06:54 by atorma            #+#    #+#             */
/*   Updated: 2024/09/18 19:41:47 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <pthread.h>
#include <sys/time.h>
#include <time.h>

int			threads_init(t_mrt *mrt, t_scene *scene);
void		threads_wait(t_mrt *mrt);
void		threads_join(t_mrt *mrt);

long long	time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec) * 1000) + (tv.tv_usec / 1000));
}

void	render_image(t_mrt *mrt)
{
	long long	ms_start;
	long long	ms_end;

	pthread_mutex_lock(&mrt->lock);
	mrt->threads_finished = 0;
	mrt->do_render = 1;
	pthread_cond_broadcast(&mrt->notify);
	pthread_mutex_unlock(&mrt->lock);
	ms_start = time_ms();
	threads_wait(mrt);
	ms_end = time_ms();
	printf("render took: %lldms, threads: %d, block_size: %d\n", ms_end
		- ms_start, THREAD_COUNT, BLOCK_SIZE);
}

void	render(t_mrt *mrt, t_scene *scene)
{
	const mlx_image_t	*img = mrt->img;

	ft_bzero(img->pixels, img->width * img->height * sizeof(int));
	mrt->scene = scene;
	ft_init_cam(&scene->cam);
	ft_set_cam_matrices(&scene->cam);
	ft_set_all_objs_matrices(scene);
	render_image(mrt);
}
