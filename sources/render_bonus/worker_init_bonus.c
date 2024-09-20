/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker_init_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:35:09 by atorma            #+#    #+#             */
/*   Updated: 2024/09/20 15:49:08 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	worker_init(t_mrt *mrt, t_scene *scene, t_worker *worker, int i)
{
	worker->mrt = mrt;
	worker->scene = scene;
	worker->index = i;
	return (ft_init_xs(&worker->xs));
}

void	workers_free(t_mrt *mrt, size_t	count)
{
	size_t	i;

	if (mrt->workers == NULL)
		return ;
	i = 0;
	while (i < count)
	{
		ft_free_xs(&mrt->workers[i].xs);
		i++;
	}
	free(mrt->workers);
	mrt->workers = NULL;
}

int	workers_init(t_mrt *mrt, t_scene *scene)
{
	size_t		i;
	t_worker	*worker;

	i = 0;
	mrt->workers = ft_calloc(1, sizeof(t_worker) * THREAD_COUNT);
	if (!mrt->workers)
		return (0);
	while (i < THREAD_COUNT)
	{
		worker = (t_worker *)&mrt->workers[i];
		if (!worker_init(mrt, scene, worker, i))
		{
			workers_free(mrt, i);
			return (0);
		}
		i++;
	}
	return (1);
}
