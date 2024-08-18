/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:47:44 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/18 12:11:18 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

int	main(int ac, char **av)
{
	t_mrt	mrt;

	ft_init_stc(&mrt, ac, av);
	mlx_close_hook(mrt.mlx, &ft_close_hook, &mrt);
	mlx_key_hook(mrt.mlx, &ft_keyboard_hooks, &mrt);
	ft_show_img(&mrt);
	//mlx_loop_hook(mrt.mlx, ft_loop_hook, &mrt);
	mlx_loop(mrt.mlx);
	mlx_terminate(mrt.mlx);
	return (0);
}
