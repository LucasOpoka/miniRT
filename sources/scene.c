
#include "../libft/libft.h"
#include "../includes/miniRT.h"
#include "../includes/parser.h"

int	scene_init(t_scene *scene)
{
	ft_init_void_arr(&scene->lights);
	ft_init_void_arr(&scene->shapes);

	t_light *light3 = malloc(sizeof(t_light));
	light3->type = t_directional;
	light3->intensity = 0.2;
	light3->direction = ft_create_vct(1, 4, 4);
	
	ft_void_arr_add(&scene->lights, light3);
	return (1);
}

void	scene_free(t_scene *scene)
{
	ft_free_void_arr(&scene->lights);
	ft_free_void_arr(&scene->shapes);
}
