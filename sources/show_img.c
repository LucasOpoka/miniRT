/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lopoka@student.hive.fi>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:55:43 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/23 20:06:14 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

int		threads_init(t_mrt *mrt, t_scene *scene);
void	threads_wait(t_mrt *mrt);
void	threads_join(t_mrt *mrt);


long long time_ms(void)
{
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}

void	render_image(t_mrt *mrt, t_scene *scene)
{
	// Init camera
	ft_init_camera(&scene->camera);
	ft_set_camera_matrices(&scene->camera);
	ft_set_all_shapes_matrices(scene);

	threads_init(mrt, scene);
	sleep(1);
	
	pthread_mutex_lock(&mrt->lock);

	mrt->threads_finished = 0;
	mrt->do_render = 1;

	pthread_cond_broadcast(&mrt->notify);

	pthread_mutex_unlock(&mrt->lock);

	long long ms_start = time_ms();
	threads_wait(mrt);
	long long ms_end = time_ms();
	printf("render took: %lldms, threads: %d, block_size: %d\n",
			ms_end - ms_start, MAX_THREADS, BLOCK_SIZE);
	mlx_image_to_window(mrt->mlx, mrt->img, 0, 0);
}
