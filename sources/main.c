/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:47:44 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/20 16:22:48 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/bvh.h"
#include "../includes/miniRT.h"

void	scene_free(t_scene *scene);
void	render(t_mrt *mrt, t_scene *scene);
void	uninit_mlx(t_mrt *mrt);
int		init_minirt(t_mrt *mrt, t_scene *scene);

int	main(int ac, char **av)
{
	t_mrt	mrt;
	t_scene	scene;

	ft_bzero(&mrt, sizeof(t_mrt));
	ft_bzero(&scene, sizeof(t_scene));

	if (ac != 2)
	{
		printf("Usage: ./miniRT <scene.rt file>\n");
		return (EXIT_FAILURE);
	}
	if (ft_strcmp(av[1], "test") == 0)
		scene = get_test_scene();
	else if (!parse_file(av[1], &scene))
		return (EXIT_FAILURE);
	if (!init_minirt(&mrt, &scene))
	{
		scene_free(&scene);
		return (EXIT_FAILURE);
	}
	render(&mrt, &scene);
	mlx_loop(mrt.mlx);
	mlx_terminate(mrt.mlx);
	scene_free(&scene);
	return (EXIT_SUCCESS);
}
