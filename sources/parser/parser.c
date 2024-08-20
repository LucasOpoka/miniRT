
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
double	ft_atof(const char *s);
t_vct	ft_create_vct(float x, float y, float z);
t_clr	ft_create_clr(float r, float g, float b);
void	fill_vector(t_vct *vector, char	*s);
void	fill_color(t_clr *vector, char	*s);

void	print_vector(t_vct v)
{
	printf("VECTOR: x: %f, y: %f, z: %f\n", v.x, v.y, v.z);
}

void	print_color(t_clr v)
{
	printf("COLOR: r: %f, g: %f, b: %f\n", v.r, v.g, v.b);
}

int	camera_add(t_scene *scene, char **elem)
{
	fill_vector(&scene->camera.position, elem[1]);
	fill_vector(&scene->camera.direction, elem[2]);
	scene->camera.fov = ft_atof(elem[3]);
	print_vector(scene->camera.position);
	print_vector(scene->camera.direction);
	printf("scene->camera.fov: %f\n", scene->camera.fov);
	return (1);
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


int	shape_add(t_scene *scene, char **elem, size_t elem_size, int id)
{
	t_shape *shape = malloc(sizeof(t_shape));

	if (!shape)
		return (0);
	shape->type = t_sphere;
	shape->radius = 1;
	shape->specular = 500;
	shape->reflective = 0.2;
	if (id == ID_SPHERE || id == ID_CYLINDER)
		shape->radius = ft_atof(elem[2]);
	else if (id == ID_PLANE)
		fill_vector(&shape->orientation, elem[2]);
	fill_vector(&shape->position, elem[1]);
	fill_color(&shape->color, elem[elem_size - 1]);


	print_vector(shape->position);
	print_color(shape->color);

	ft_void_arr_add(&scene->shapes, shape);
	return (1);
}

int	parse_shape(t_scene *scene, char **shape, int id)
{
	size_t	i;
	size_t	elem_size;

	i = 0;
	printf("SHAPE: \t%d", id);

	elem_size = array_size(shape);
	//shape_validate()
	while (shape[i])
	{
		printf("\t%s", shape[i]);
		i++;
	}
	shape_add(scene, shape, elem_size, id);
	printf("\n");
	return (1);
}

int	parse_line(t_scene *scene, char **line)
{
	int		ret;
	int		id;

	id = identifier_type(line[0]);

	ret = 1;
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
	printf("line_count: %zu\n", i);
	return (1);
}


int	init_scene(t_scene *scene)
{
	ft_init_void_arr(&scene->shapes);
	ft_init_void_arr(&scene->lights);

	scene->camera.fov = FOV;

	scene->camera.position.x = 0;
	scene->camera.position.y = 0;
	scene->camera.position.z = 0;
	scene->camera.position.w = 1;

	scene->camera.direction.x = 0;
	scene->camera.direction.y = 0;
	scene->camera.direction.z = 1;
	scene->camera.direction.w = 0;

	t_light *light2 = malloc(sizeof(t_light));
	light2->type = t_point;
	light2->intensity = 0.6;
	light2->position = ft_create_vct(2, 1, 0);
	
	t_light *light3 = malloc(sizeof(t_light));
	light3->type = t_directional;
	light3->intensity = 0.2;
	light3->direction = ft_create_vct(1, 4, 4);
	
	ft_void_arr_add(&scene->lights, light2);
	ft_void_arr_add(&scene->lights, light3);

	return (1);
}

int	parse_file(char *file, t_scene *scene)
{
	char	***matrix;
	char	*data;
	int		ret;

	ret = 0;
	data = file_load(file);
	if (!data)
		return (0);
	printf("scene %s raw data:\n %s\n-------------\n", file, data);

	init_scene(scene);
	matrix = array_matrix(data);
	ret = parse_scene(scene, matrix);
	array_matrix_free(matrix);

	free(data);
	return (ret);
}
