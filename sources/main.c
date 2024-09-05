/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:47:44 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/05 20:17:12 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"
#include "../includes/bvh.h"

void	scene_free(t_scene *scene);
void	render(t_mrt *mrt, t_scene *scene);
int		threads_init(t_mrt *mrt, t_scene *scene);
void	close_hook(void *ptr);

void	print_objects(t_scene *scene)
{
	size_t	i = 0;
	char	*type = "unknown";
	while (i < scene->objs.i)
	{
		t_obj *obj = (t_obj *) scene->objs.arr[i++];
		if (obj->type == t_sphere)
			type = "sphere";
		if (obj->type == t_cylinder)
			type = "cylinder";
		if (obj->type == t_plane)
			type = "plane";
		printf("---- OBJ %s ----\n", type);
		printf("radius: %f\n", obj->radius);
		printf("specular: %f\n", obj->specular);
		printf("diffuse: %f\n", obj->diffuse);
		printf("shininess: %d\n", obj->shininess);
		printf("reflective: %f\n", obj->reflective);
		printf("refractive: %f\n", obj->refractive);
		printf("transparency: %f\n", obj->transparency);
	}
}

int	main(int ac, char **av)
{
	t_mrt	mrt;
	t_scene	scene;

	if (ac != 2)
	{
		printf("Usage: ./miniRT <scene.rt file>\n");
		return (EXIT_FAILURE);
	}
	if (ft_strcmp(av[1], "test") == 0)
	{
		scene = get_test_scene();
	}
	else if (!parse_file(av[1], &scene))
	{
		return (EXIT_FAILURE);
	}
	printf("using scene: %s\n", av[1]);
	print_objects(&scene);

	scene.bvh.root = bvh_build(&scene);

	if (!threads_init(&mrt, &scene))
	{
		printf("Failed to init threads\n");
		return (0);
	}
	init_mlx(&mrt);
	mlx_close_hook(mrt.mlx, &close_hook, &mrt);
	mlx_key_hook(mrt.mlx, &ft_keyboard_hooks, &mrt);
	
	render(&mrt, &scene);
	mlx_loop(mrt.mlx);
	mlx_terminate(mrt.mlx);
	scene_free(&scene);
	return (EXIT_SUCCESS);
}
