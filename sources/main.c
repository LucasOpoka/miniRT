/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:47:44 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/21 15:48:55 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

void	scene_free(t_scene *scene);
//int		threads_init(t_mrt *mrt);
//void	threads_join(t_mrt *mrt);

int	main(int ac, char **av)
{
	t_mrt	mrt;
	t_scene	scene;

	/*
	if (ac != 2)
	{
		printf("Usage: ./miniRT <scene.rt file>\n");
		threads_init(&mrt);
		threads_join(&mrt);
		return (EXIT_FAILURE);
	}
	if (!parse_file(av[1], &scene))
	{
		ft_putstr_fd("Error\n", 2);
		return (EXIT_FAILURE);
	}
	printf("using scene: %s\n", av[1]);
	*/
	ft_init_stc(&mrt);
	mlx_close_hook(mrt.mlx, &ft_close_hook, &mrt);
	mlx_key_hook(mrt.mlx, &ft_keyboard_hooks, &mrt);
	
	(void) ac;
	(void) av;
	scene = get_test_scene();
	ft_show_img(&mrt, &scene);
	//mlx_loop_hook(mrt.mlx, ft_loop_hook, &mrt);
	//We probably only want to render the image on changes, not every frame in the hook
	//Otherwise our performance will be garbage since raytracing is very expensive
	mlx_loop(mrt.mlx);
	mlx_terminate(mrt.mlx);
	scene_free(&scene);
	return (EXIT_SUCCESS);
}
