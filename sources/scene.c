
#include "../libft/libft.h"
#include "../includes/miniRT.h"
#include "../includes/parser.h"

int	scene_init(t_scene *scene)
{
	ft_init_void_arr(&scene->lights);
	ft_init_void_arr(&scene->objs);

	t_light *light3 = malloc(sizeof(t_light));
	light3->type = t_diral;
	light3->intensity = 0.2;
	light3->dir = ft_create_vct(1, 4, 4);
	
	ft_void_arr_add(&scene->lights, light3);
	return (1);
}

void	scene_free(t_scene *scene)
{
	ft_free_void_arr(&scene->lights);
	ft_free_void_arr(&scene->objs);
	free(scene->bvh_root);
	free(scene->bvh_index);
}
