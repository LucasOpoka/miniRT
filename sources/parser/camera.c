#include "../../libft/libft.h"
#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

static int	validate_fov(char **elem)
{
	size_t	fov_len;
	double	fov_val;

	fov_len = ft_strlen(elem[3]);
	if (!str_isdigit(elem[3]) || (fov_len > 3))
		return (0);
	fov_val = ft_atof(elem[3]);
	if (fov_val < 0.0 || fov_val > 180.0)
		return (0);
	return (1);
}

int	camera_add(t_scene *scene, char **elem)
{
	if (!validate_fov(elem))
		return (0);
	fill_vector(&scene->camera.position, elem[1]);
	fill_vector(&scene->camera.direction, elem[2]);
	scene->camera.position.w = 1;
	scene->camera.direction.w = 0;
	scene->camera.fov = ft_atof(elem[3]);
	print_vector(scene->camera.position);
	print_vector(scene->camera.direction);
	printf("scene->camera.fov: %f\n", scene->camera.fov);
	return (1);
}
