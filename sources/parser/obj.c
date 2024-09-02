/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:07:54 by atorma            #+#    #+#             */
/*   Updated: 2024/08/31 17:42:53 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

int	validate_orientation(t_vct v);

static int	sphere_add(t_obj *obj, char **elem)
{
	if (!str_isdouble(elem[2]))
		return (0);
	obj->type = t_sphere;
	obj->specular = 500;
	obj->reflective = 0.2;
	fill_vector(&obj->pos, elem[1]);
	obj->radius = ft_atof(elem[2]);
	if ((obj->radius <= 0.0) || !fill_color(&obj->color, elem[3]))
		return (0);
	obj->scale = ft_create_vct(1, 1, 1);
	obj->orientation = ft_create_vct(0, 1, 0);
	obj->diffuse = 0.5;
	obj->shininess = 500;
	return (1);
}

static int	plane_add(t_obj *obj, char **elem)
{
	obj->type = t_plane;
	obj->specular = 500;
	obj->reflective = 0.2;
	fill_vector(&obj->pos, elem[1]);
	fill_vector(&obj->orientation, elem[2]);
	if (!fill_color(&obj->color, elem[3]))
		return (0);
	if (!validate_orientation(obj->orientation))
		return (0);
	return (1);
}

static int	cylinder_add(t_obj *obj, char **elem)
{
	obj->type = t_cylinder;
	obj->specular = 500;
	obj->reflective = 0.2;
	fill_vector(&obj->pos, elem[1]);
	fill_vector(&obj->orientation, elem[2]);
	obj->radius = ft_atof(elem[3]);
	obj->height = ft_atof(elem[4]);
	if (obj->radius <= 0.0 || obj->height <= 0.0)
		return (0);
	if (!fill_color(&obj->color, elem[5]))
		return (0);
	if (!validate_orientation(obj->orientation))
		return (0);
	return (1);
}

int	obj_add(t_scene *scene, char **elem, int id)
{
	t_obj	*obj;
	int		ret;

	ret = 0;
	if (!validate_vector(elem[1]))
		return (0);
	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (0);
	if (id == ID_SPHERE)
		ret = sphere_add(obj, elem);
	else if (id == ID_PLANE)
		ret = plane_add(obj, elem);
	else if (id == ID_CYLINDER)
		ret = cylinder_add(obj, elem);
	if (!ret)
	{
		free(obj);
		return (0);
	}
	ft_void_arr_add(&scene->objs, obj);
	return (1);
}
