
#include "../../libft/libft.h"
#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

size_t	array_size(char **arr);
void	array_free(char **arr);
char	***array_matrix(char *data);
void	array_matrix_free(char ***arr);
void	print_matrix(char ***m);
char	*file_load(char *file);
int		validate_identifiers(char ***elements);
t_vct	ft_create_vct(float x, float y, float z);
t_clr	ft_create_clr(float r, float g, float b);
int		sphere_add(t_shape *shape, char **elem);
int		plane_add(t_shape *shape, char **elem);
int		cylinder_add(t_shape *shape, char **elem);
int		camera_add(t_scene *scene, char **elem);

void	print_vector(t_vct v)
{
	printf("VECTOR: x: %f, y: %f, z: %f\n", v.x, v.y, v.z);
}

void	print_color(t_clr v)
{
	printf("COLOR: r: %f, g: %f, b: %f\n", v.r, v.g, v.b);
}

int	light_add(t_scene *scene, char **elem, int id)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (id == ID_AMBIENT)
	{
		if (!validate_ratio(elem[1], 0.0, 1.0))
			return (0);
		light->type = t_ambient;
		light->intensity = ft_atof(elem[1]);
		fill_color(&light->color, elem[2]);
		printf("ambient intensity: %f\n", light->intensity);
	}
	if (id == ID_LIGHT)
	{
		if (!validate_ratio(elem[2], 0.0, 1.0))
			return (0);
		light->type = t_point;
		fill_vector(&light->position, elem[1]);
		light->intensity = ft_atof(elem[2]);
		fill_color(&light->color, elem[3]);
		printf("L intensity: %f\n", light->intensity);
	}
	ft_void_arr_add(&scene->lights, light);
	return (1);
}

int	parse_object(t_scene *scene, char **object, int id)
{
	int		ret;

	ret = 0;
	if (id == ID_CAMERA)
		ret = camera_add(scene, object);
	else if (id == ID_AMBIENT || id == ID_LIGHT)
		ret = light_add(scene, object, id);
	return (ret);
}

int	parse_shape(t_scene *scene, char **line, int id)
{
	t_shape *shape;
	int		ret;

	ret = 0;
	shape = malloc(sizeof(t_shape));
	if (!shape)
		return (0);
	if (id == ID_SPHERE)
		ret = sphere_add(shape, line);
	else if (id == ID_PLANE)
		ret = plane_add(shape, line);
	else if (id == ID_CYLINDER)
		ret = cylinder_add(shape, line);
	if (!ret)
	{
		free(shape);
		return (0);
	}
	ft_void_arr_add(&scene->shapes, shape);
	return (1);
}

int	parse_line(t_scene *scene, char **line)
{
	int		ret;
	int		id;

	id = identifier_type(line[0]);

	ret = 0;
	if (id >= ID_SPHERE)
		ret = parse_shape(scene, line, id);
	else if (id >= ID_AMBIENT)
		ret = parse_object(scene, line, id);
	return (ret);
}

int	parse_scene(t_scene *scene, char ***matrix)
{
	size_t	i;

	i = 0;
	if (!matrix)
		return (0);
	if (!validate_identifiers(matrix))
	{
		printf("Error: validate_identifiers\n");
		return (0);
	}
	while (matrix[i])
	{
		if (!parse_line(scene, matrix[i]))
			return (0);
		i++;
	}
	return (1);
}


int	parse_file(char *file, t_scene *scene)
{
	char	***matrix;
	char	*data;
	int		ret;

	ret = 0;
	ft_bzero(scene, sizeof(t_scene));
	data = file_load(file);
	if (!data)
		return (0);
	scene_init(scene);
	matrix = array_matrix(data);
	ret = parse_scene(scene, matrix);
	array_matrix_free(matrix);

	free(data);
	return (ret);
}
