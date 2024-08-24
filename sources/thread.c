
#include "../libft/libft.h"
#include "../includes/miniRT.h"
#include <pthread.h>

t_worker	*worker_init(t_mrt *mrt, t_scene *scene, int i);
void	*worker_routine(void *ptr);

int	threads_init(t_mrt *mrt, t_scene *scene)
{
	size_t	i;

	i = 0;
	mrt->do_render = 0;
	if (pthread_mutex_init(&mrt->lock, NULL) != 0)
		return (0);
	if (pthread_cond_init(&mrt->notify, NULL) != 0)
		return (0);
	if (pthread_cond_init(&mrt->complete, NULL) != 0)
		return (0);
	while (i < MAX_THREADS)
	{
		t_worker *worker = worker_init(mrt, scene, i);
		if (pthread_create(&mrt->threads[i], NULL, worker_routine, worker) != 0)
		{
			free(worker);
			return (0);
		}
		i++;
		mrt->thread_count = i;
	}
	return (1);
}

void	threads_wait(t_mrt *mrt)
{
	pthread_mutex_lock(&mrt->lock);

	while (mrt->threads_finished != MAX_THREADS)
		pthread_cond_wait(&mrt->complete, &mrt->lock);

	mrt->do_render = 0;
	mrt->threads_finished = 0;
	pthread_cond_broadcast(&mrt->notify);
	pthread_mutex_unlock(&mrt->lock);
}

void	threads_join(t_mrt *mrt)
{
	size_t	i;

	i = 0;
	while (i < mrt->thread_count)
	{
		pthread_join(mrt->threads[i], NULL);
		i++;
	}
}
