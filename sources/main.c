/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:47:44 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/18 12:16:30 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft/libft.h"
#include "../includes/miniRT.h"
#include "../includes/parser.h"

int	main(int ac, char **av)
{
	t_mrt	mrt;
	t_scene	scene;

	if (ac == 2)
	{
		if (!parse_file(av[1], &scene))
			ft_putstr_fd("Error\n", 2);
		return (0);
	}
	ft_init_stc(&mrt, ac, av);
	mlx_close_hook(mrt.mlx, &ft_close_hook, &mrt);
	mlx_key_hook(mrt.mlx, &ft_keyboard_hooks, &mrt);
	ft_show_img(&mrt);
	//mlx_loop_hook(mrt.mlx, ft_loop_hook, &mrt);
	mlx_loop(mrt.mlx);
	mlx_terminate(mrt.mlx);
	return (0);
}
