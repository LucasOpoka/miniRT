
#include "../../libft/libft.h"
#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

int	light_add_ambient(t_light *light, char **elem)
{
	if (!validate_ratio(elem[1], 0.0, 1.0))
		return (0);
	if (!fill_color(&light->color, elem[2]))
		return (0);
	light->type = t_ambient;
	light->intensity = ft_atof(elem[1]);
	printf("ambient intensity: %f\n", light->intensity);
	return (1);
}

int	light_add_point(t_light *light, char **elem)
{
	if (!validate_vector(elem[1]))
		return (0);
	if (!validate_ratio(elem[2], 0.0, 1.0))
		return (0);
	light->type = t_point;
	fill_vector(&light->position, elem[1]);
	light->intensity = ft_atof(elem[2]);
	if (!fill_color(&light->color, elem[3]))
		return (0);
	printf("L intensity: %f\n", light->intensity);
	return (1);
}

int	light_add(t_scene *scene, char **elem, int id)
{
	t_light	*light;
	int		ret;

	ret = 0;
	light = malloc(sizeof(t_light));
	if (!light)
		return (0);
	if (id == ID_AMBIENT)
		ret = light_add_ambient(light, elem);
	else if (id == ID_LIGHT)
		ret = light_add_point(light, elem);
	if (!ret)
	{
		free(light);
		return (0);
	}
	ft_void_arr_add(&scene->lights, light);
	return (ret);
}
