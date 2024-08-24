/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:07:54 by atorma            #+#    #+#             */
/*   Updated: 2024/08/24 18:13:04 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

int	validate_orientation(t_vct v);

static int	sphere_add(t_shape *shape, char **elem)
{
	if (!str_isfloat(elem[2]))
		return (0);
	shape->type = t_sphere;
	shape->specular = 500;
	shape->reflective = 0.2;
	fill_vector(&shape->position, elem[1]);
	shape->radius = ft_atof(elem[2]);
	if ((shape->radius < 0.0) || !fill_color(&shape->color, elem[3]))
		return (0);
	shape->scale = ft_create_vct(1, 1, 1);
	shape->orientation = ft_create_vct(0, 1, 0);
	return (1);
}

static int	plane_add(t_shape *shape, char **elem)
{
	shape->type = t_plane;
	shape->specular = 500;
	shape->reflective = 0.2;
	fill_vector(&shape->position, elem[1]);
	fill_vector(&shape->orientation, elem[2]);
	if (!fill_color(&shape->color, elem[3]))
		return (0);
	if (!validate_orientation(shape->orientation))
		return (0);
	return (1);
}

static int	cylinder_add(t_shape *shape, char **elem)
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
	if (!validate_orientation(shape->orientation))
		return (0);
	return (1);
}

int	shape_add(t_scene *scene, char **elem, int id)
{
	t_shape	*shape;
	int		ret;

	ret = 0;
	if (!validate_vector(elem[1]))
		return (0);
	shape = malloc(sizeof(t_shape));
	if (!shape)
		return (0);
	if (id == ID_SPHERE)
		ret = sphere_add(shape, elem);
	else if (id == ID_PLANE)
		ret = plane_add(shape, elem);
	else if (id == ID_CYLINDER)
		ret = cylinder_add(shape, elem);
	if (!ret)
	{
		free(shape);
		return (0);
	}
	ft_void_arr_add(&scene->shapes, shape);
	return (1);
}
