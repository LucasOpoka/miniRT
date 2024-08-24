/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:14:55 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/04 14:15:03 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

void	ft_close_hook(void *vd)
{
	ft_close((t_mrt *)vd);
}

void	ft_loop_hook(void *vd)
{
	(void)vd;
	//ft_show_img((t_mrt *) vd);
}

void	render_image(t_mrt *mrt);

void	ft_keyboard_hooks(mlx_key_data_t k_data, void *vd)
{
	t_mrt	*mrt;

	mrt = (t_mrt *)vd;
	if (k_data.key == MLX_KEY_ESCAPE && k_data.action == MLX_PRESS)
		ft_close(mrt);
	if (k_data.key == MLX_KEY_C && k_data.action == MLX_PRESS)
		render_image(mrt);
}
