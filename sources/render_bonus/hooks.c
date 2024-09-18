/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:14:55 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/18 17:41:30 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/miniRT.h"
#include <pthread.h>

void	render_image(t_mrt *mrt);

void	threads_wait(t_mrt *mrt);
void	threads_join(t_mrt *mrt);
void	uninit_mlx(t_mrt *mrt);

void	close_hook(void *ptr)
{
	t_mrt	*mrt;

	mrt = ptr;
	threads_wait(mrt);
	pthread_mutex_lock(&mrt->lock);
	mrt->exit = 1;
	pthread_cond_broadcast(&mrt->notify);
	printf("threads notified...\n");
	pthread_mutex_unlock(&mrt->lock);
	uninit_mlx(mrt);
	threads_join(mrt);
	printf("threads joined\n");
}

void	ft_keyboard_hooks(mlx_key_data_t k_data, void *vd)
{
	t_mrt	*mrt;

	mrt = (t_mrt *)vd;
	if (k_data.key == MLX_KEY_ESCAPE && k_data.action == MLX_PRESS)
		close_hook(mrt);
	if (k_data.key == MLX_KEY_C && k_data.action == MLX_PRESS)
		render_image(mrt);
}
