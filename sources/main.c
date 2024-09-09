/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:47:44 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/09 20:21:29 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"
#include "../includes/bvh.h"

void	scene_free(t_scene *scene);
void	render(t_mrt *mrt, t_scene *scene);
int	init_minirt(t_mrt *mrt, t_scene *scene);

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
	ft_bzero(&mrt, sizeof(t_mrt));
	ft_bzero(&scene, sizeof(t_scene));
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

	if (init_minirt(&mrt, &scene))
	{
		render(&mrt, &scene);
		mlx_loop(mrt.mlx);
		mlx_terminate(mrt.mlx);
	}
	scene_free(&scene);
	return (EXIT_SUCCESS);
}
