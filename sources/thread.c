
#include "../libft/libft.h"
#include "../includes/miniRT.h"
#include <pthread.h>

void	*worker_routine(void *ptr);

t_worker	*worker_init(t_mrt *mrt, t_scene *scene, int i)
{
	t_worker	*worker;

	worker = malloc(sizeof(t_worker));
	worker->mrt = mrt;
	worker->scene = scene;
	worker->index = i;
	return (worker);
}

int	threads_init(t_mrt *mrt, t_scene *scene)
{
	size_t	i;

	i = 0;
	if (pthread_mutex_init(&mrt->lock, NULL) != 0)
		return (0);
	pthread_mutex_lock(&mrt->lock);
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

void	threads_join(t_mrt *mrt)
{
	size_t	i;

	i = 0;
	pthread_mutex_unlock(&mrt->lock);
	while (i < mrt->thread_count)
	{
		pthread_join(mrt->threads[i], NULL);
		i++;
	}
}
