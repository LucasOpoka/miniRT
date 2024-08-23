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

int		threads_init(t_mrt *mrt, t_scene *scene);
void	threads_wait(t_mrt *mrt);
void	threads_join(t_mrt *mrt);

long long time_ms(void) {
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}

/*
void	ft_show_img(t_mrt *mrt, t_scene *scene)
{
	t_ray		world_ray;
	t_clr		color;
	int			pixel_x;
	int			pixel_y;
	t_void_arr	intersections;

	// Init camera
	ft_init_camera(&scene->camera);
	ft_set_camera_matrices(&scene->camera);
	ft_set_all_shapes_matrices(scene);

	long long ms_start = time_ms();
	long long ms_end;
	pixel_y = 0;
	while (pixel_y < CANV_HGHT)
	{
		pixel_x = 0;
		while (pixel_x < CANV_WDTH)
		{	
			ft_init_void_arr(&intersections);
			ft_pixel_to_ray(&world_ray, pixel_x, pixel_y, &scene->camera);
			ft_get_intersections(world_ray, scene, &intersections);
			color = ft_get_color(world_ray.O, world_ray.D, scene, 3, &intersections);
			mlx_put_pixel(mrt->img, pixel_x++, pixel_y, ft_clr_to_int(color));
			ft_free_void_arr(&intersections);
		}
		pixel_y++;
	}
	ms_end = time_ms();
	printf("time_taken: %lld\n", ms_end - ms_start);
	mlx_image_to_window(mrt->mlx, mrt->img, 0, 0);
}
*/

#include <pthread.h>


#define	BLOCK_SIZE 4

void	*worker_routine(void *ptr)
{
	t_worker	*worker;
	t_mrt		*mrt;
	t_scene		*scene;
	t_void_arr	intersections;

	worker = (t_worker *)ptr;
	mrt = worker->mrt;
	scene = worker->scene;

	ft_init_void_arr(&intersections);



	int			block_count = CANV_HGHT / BLOCK_SIZE;
	int			block_size = BLOCK_SIZE;

	t_ray		world_ray;
	t_clr		color;

	int done = 0;
	while (1)
	{
		pthread_mutex_lock(&worker->mrt->lock);
		while (!worker->mrt->do_render || (done && worker->mrt->do_render))
			pthread_cond_wait(&worker->mrt->notify, &worker->mrt->lock);
		pthread_mutex_unlock(&worker->mrt->lock);
		done = 0;
	
		int i = worker->index;
		printf("worker: %d starting\n", worker->index);
		while (i < block_count)
		{
			int start_y = i * block_size;
			if (i == block_count - 1)
				block_size += CANV_HGHT % BLOCK_SIZE;
		
			int pixel_y = start_y;
			while (pixel_y < (start_y + block_size))
			{
				int pixel_x = 0;
				while (pixel_x < CANV_WDTH)
				{	
					ft_pixel_to_ray(&world_ray, pixel_x, pixel_y, &scene->camera);
					ft_get_intersections(world_ray, scene, &intersections);
					color = ft_get_color(world_ray.O, world_ray.D, scene, 3, &intersections);
					mlx_put_pixel(mrt->img, pixel_x++, pixel_y, ft_clr_to_int(color));
					intersections.i = 0;
				}
				pixel_y++;
			}
			i += MAX_THREADS;
		}
		pthread_mutex_lock(&worker->mrt->lock);
		mrt->threads_finished++;
		pthread_cond_signal(&worker->mrt->complete);
		pthread_mutex_unlock(&worker->mrt->lock);
		done = 1;
	
		printf("worker: %d finished\n", worker->index);
	}

	ft_free_void_arr(&intersections);

	free(ptr);
	return (NULL);
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
	printf("render took: %lldms\n", ms_end - ms_start);
	mlx_image_to_window(mrt->mlx, mrt->img, 0, 0);
}
