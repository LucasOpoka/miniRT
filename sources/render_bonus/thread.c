/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:29:57 by atorma            #+#    #+#             */
/*   Updated: 2024/09/19 01:38:28 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../libft/libft.h"
#include <pthread.h>

int		worker_init(t_mrt *mrt, t_scene *scene, t_worker *worker, int i);
void	*worker_routine(void *ptr);

int	threads_create(t_mrt *mrt, t_scene *scene)
{
	size_t		i;
	t_worker	*worker;

	i = 0;
	mrt->thread_count = 0;
	mrt->workers = ft_calloc(1, sizeof(t_worker) * THREAD_COUNT);
	if (!mrt->workers)
		return (0);
	while (i < THREAD_COUNT)
	{
		worker = (t_worker *)&mrt->workers[i];
		if (!worker_init(mrt, scene, worker, i))
			return (0);
		if (pthread_create(&mrt->threads[i], NULL, worker_routine, worker) != 0)
			return (0);
		i++;
		mrt->thread_count = i;
	}
	return (1);
}

int	threads_init(t_mrt *mrt, t_scene *scene)
{
	mrt->do_render = 0;
	mrt->threads_finished = 0;
	mrt->exit = 0;
	if (pthread_mutex_init(&mrt->lock, NULL) != 0)
		return (0);
	if (pthread_cond_init(&mrt->notify, NULL) != 0)
		return (0);
	if (pthread_cond_init(&mrt->complete, NULL) != 0)
		return (0);
	if (!threads_create(mrt, scene))
		return (0);
	return (1);
}

void	threads_wait(t_mrt *mrt)
{
	pthread_mutex_lock(&mrt->lock);
	while (mrt->threads_finished != THREAD_COUNT)
		pthread_cond_wait(&mrt->complete, &mrt->lock);
	mrt->do_render = 0;
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
		ft_free_xs(&mrt->workers[i].xs);
		i++;
	}
	pthread_mutex_destroy(&mrt->lock);
	pthread_cond_destroy(&mrt->notify);
	pthread_cond_destroy(&mrt->complete);
	free(mrt->workers);
}
