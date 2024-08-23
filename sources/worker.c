
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
	while (!mrt->do_render || (worker->done && mrt->do_render))
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

	while (1)
	{
		worker_wait(worker);	
		int i = worker->index;
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
		worker_signal_finish(worker);	
	}

	ft_free_void_arr(&intersections);

	free(ptr);
	return (NULL);
}
