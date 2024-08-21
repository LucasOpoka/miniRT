
#include "../libft/libft.h"
#include "../includes/miniRT.h"
#include <pthread.h>

void	*thread_routine(void *ptr)
{
	t_mrt	*mrt;

	mrt = (t_mrt *)ptr;
	pthread_mutex_lock(&mrt->lock);
	pthread_mutex_unlock(&mrt->lock);
	printf("thread_routine\n");
	return (NULL);
}

int	threads_init(t_mrt *mrt)
{
	size_t	i;

	i = 0;
	if (pthread_mutex_init(&mrt->lock, NULL) != 0)
		return (0);
	pthread_mutex_lock(&mrt->lock);
	while (i < MAX_THREADS)
	{
		if (pthread_create(&mrt->threads[i], NULL, thread_routine, mrt) != 0)
		{
			return (0);
		}
		i++;
		mrt->thread_count = i;
	}
	pthread_mutex_unlock(&mrt->lock);
	return (1);
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
