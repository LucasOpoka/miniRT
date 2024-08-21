
#include "../libft/libft.h"
#include "../includes/miniRT.h"
#include <pthread.h>

void	*thread_routine(void *ptr)
{
	(void)ptr;
	printf("thread_routine\n");
	return (NULL);
}

int	threads_init(t_mrt *mrt)
{
	size_t	i;

	i = 0;
	while (i < MAX_THREADS)
	{
		if (pthread_create(&mrt->threads[i], NULL, thread_routine, mrt) != 0)
		{
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
	while (i < mrt->thread_count)
	{
		pthread_join(mrt->threads[i], NULL);
		i++;
	}
}
