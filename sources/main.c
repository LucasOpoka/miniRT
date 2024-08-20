/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:47:44 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/18 14:25:33 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

int	main(int ac, char **av)
{
	t_mrt	mrt;
	t_scene	scene;

	ft_bzero(&scene, sizeof(t_scene));
	if (ac == 2)
	{
		if (!parse_file(av[1], &scene))
		{
			ft_putstr_fd("Error\n", 2);
			return (0);
		}
		printf("using scene: %s\n", av[1]);
	}
	else
	{
		scene = get_test_scene();
		printf("using test_scene()\n");
	}
	ft_init_stc(&mrt, ac, av);
	mlx_close_hook(mrt.mlx, &ft_close_hook, &mrt);
	mlx_key_hook(mrt.mlx, &ft_keyboard_hooks, &mrt);
	ft_show_img(&mrt, &scene);
	//mlx_loop_hook(mrt.mlx, ft_loop_hook, &mrt);
	mlx_loop(mrt.mlx);
	mlx_terminate(mrt.mlx);
	return (0);
}
