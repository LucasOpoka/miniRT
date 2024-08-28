/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:14:55 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/28 19:15:58 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"
#include <pthread.h>

void	render_image(t_mrt *mrt);

void	threads_wait(t_mrt *mrt);
void	threads_join(t_mrt *mrt);

static void close_window(t_mrt *mrt)
{
	pthread_mutex_lock(&mrt->lock);
	mrt->exit = 1;
	pthread_mutex_unlock(&mrt->lock);
	threads_wait(mrt);
	printf("closing... threads finished\n");
	if (mrt->img)
		mlx_delete_image(mrt->mlx, mrt->img);
	if (mrt->mlx)
		mlx_close_window(mrt->mlx);
	threads_join(mrt);
	printf("threads joined\n");
}

void	ft_keyboard_hooks(mlx_key_data_t k_data, void *vd)
{
	t_mrt	*mrt;

	mrt = (t_mrt *)vd;
	if (k_data.key == MLX_KEY_ESCAPE && k_data.action == MLX_PRESS)
		close_window(mrt);
	if (k_data.key == MLX_KEY_C && k_data.action == MLX_PRESS)
		render_image(mrt);
}
