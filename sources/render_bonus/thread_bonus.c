/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:29:57 by atorma            #+#    #+#             */
/*   Updated: 2024/09/20 15:49:02 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <pthread.h>

int		locks_init(t_mrt *mrt);
void	locks_destroy(t_mrt *mrt);
void	workers_free(t_mrt *mrt, size_t count);
int		workers_init(t_mrt *mrt, t_scene *scene);
void	*worker_routine(void *ptr);
void	threads_join(t_mrt *mrt);

int	threads_create(t_mrt *mrt)
{
	size_t		i;
	t_worker	*worker;

	i = 0;
	mrt->thread_count = 0;
	while (i < THREAD_COUNT)
	{
		worker = (t_worker *)&mrt->workers[i];
		if (pthread_create(&mrt->threads[i], NULL, worker_routine, worker) != 0)
		{
			threads_join(mrt);
			return (0);
		}
		i++;
		mrt->thread_count = i;
	}
	return (1);
}

int	threads_init(t_mrt *mrt, t_scene *scene)
{
	if (!locks_init(mrt))
		return (0);
	if (!workers_init(mrt, scene) || !threads_create(mrt))
	{
		locks_destroy(mrt);
		return (0);
	}
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
	if (!mrt->thread_count)
		return ;
	while (i < mrt->thread_count)
	{
		pthread_join(mrt->threads[i], NULL);
		i++;
	}
	locks_destroy(mrt);
	workers_free(mrt, mrt->thread_count);
	mrt->thread_count = 0;
}
