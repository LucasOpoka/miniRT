
#include "../../libft/libft.h"
#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

size_t	array_size(char **arr);
void	array_free(char **arr);
char	***array_matrix(char *data);
void	print_matrix(char ***m);
void	array_matrix_free(char ***arr);
char	*file_load(char *file);
int		validate_identifiers(char ***elements);
t_vct	ft_create_vct(float x, float y, float z);
t_clr	ft_create_clr(float r, float g, float b);
int		sphere_add(t_shape *shape, char **elem);
int		plane_add(t_shape *shape, char **elem);
int		cylinder_add(t_shape *shape, char **elem);

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
	t_light *light = malloc(sizeof(t_light));
	if (id == ID_AMBIENT)
	{
		light->type = t_ambient;
		light->intensity = ft_atof(elem[1]);
		printf("ambient intensity: %f\n", light->intensity);
		//light->color here
	}
	/*
	if (id == ID_LIGHT)
	{
		light->type = t_light;
	}
	*/
	ft_void_arr_add(&scene->lights, light);
	return (1);
}

int	camera_add(t_scene *scene, char **elem)
{
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

int	parse_object(t_scene *scene, char **object, int id)
{
	size_t	i;

	i = 0;
	printf("OBJ:\t%d", id);
	while (object[i])
	{
		printf("\t%s", object[i]);
		i++;
	}
	printf("\n");
	if (id == ID_CAMERA)
		camera_add(scene, object);
	else if (id == ID_AMBIENT)
		light_add(scene, object, id);
	return (1);
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
