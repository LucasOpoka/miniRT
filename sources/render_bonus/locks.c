/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:49:01 by atorma            #+#    #+#             */
/*   Updated: 2024/09/19 20:50:39 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <pthread.h>

int	locks_init(t_mrt *mrt)
{
	if (pthread_mutex_init(&mrt->lock, NULL) != 0)
		return (0);
	if (pthread_cond_init(&mrt->notify, NULL) != 0)
	{
		pthread_mutex_destroy(&mrt->lock);
		return (0);
	}
	if (pthread_cond_init(&mrt->complete, NULL) != 0)
	{
		pthread_mutex_destroy(&mrt->lock);
		pthread_cond_destroy(&mrt->notify);
		return (0);
	}
	return (1);
}

void	locks_destroy(t_mrt *mrt)
{
	pthread_mutex_destroy(&mrt->lock);
	pthread_cond_destroy(&mrt->notify);
	pthread_cond_destroy(&mrt->complete);
}
