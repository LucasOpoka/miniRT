#include "../../libft/libft.h"
#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

int	sphere_add(t_shape *shape, char **elem)
{
	shape->type = t_sphere;
	shape->specular = 500;
	shape->reflective = 0.2;
	fill_vector(&shape->position, elem[1]);
	shape->radius = ft_atof(elem[2]);
	if (!fill_color(&shape->color, elem[3]))
		return (0);
	return (1);
}

int	plane_add(t_shape *shape, char **elem)
{
	shape->type = t_plane;
	shape->specular = 500;
	shape->reflective = 0.2;
	fill_vector(&shape->position, elem[1]);
	fill_vector(&shape->orientation, elem[2]);
	if (!fill_color(&shape->color, elem[3]))
		return (0);
	return (1);
}

int	cylinder_add(t_shape *shape, char **elem)
{
	shape->type = t_cylinder;
	shape->specular = 500;
	shape->reflective = 0.2;
	fill_vector(&shape->position, elem[1]);
	fill_vector(&shape->orientation, elem[2]);
	shape->radius = ft_atof(elem[3]);
	shape->height = ft_atof(elem[4]);
	if (!fill_color(&shape->color, elem[5]))
		return (0);
	return (1);
}
