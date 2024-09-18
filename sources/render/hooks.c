/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:14:55 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/18 17:41:03 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/miniRT.h"

void	render_image(t_mrt *mrt);

void	uninit_mlx(t_mrt *mrt);

void	close_hook(void *ptr)
{
	t_mrt	*mrt;

	mrt = ptr;
	uninit_mlx(mrt);
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
