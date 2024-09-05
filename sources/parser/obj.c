/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:07:54 by atorma            #+#    #+#             */
/*   Updated: 2024/09/05 20:18:04 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

int	validate_orientation(t_vct v);

/*
*   object bonus fields after mandatory
*   <specular> <diffuse> <shininess> <reflective> <refractive> <transparency> <scale vector>
*   +7 fields
*/

#ifdef BONUS

static int	obj_validate_bonus(t_obj *obj)
{
	if (obj->transparency < 0 || obj->transparency > 1.0)
		return (0);
	if (obj->reflective < 0 || obj->reflective > 1.0)
		return (0);
	if (obj->diffuse < 0 || obj->diffuse > 1.0)
		return (0);
	if (obj->specular < 0 || obj->specular > 1.0)
		return (0);
	if (obj->shininess < 0 || obj->refractive < 0)
		return (0);
	return (1);
}

static int	obj_add_bonus_fields(t_obj *obj, char **elem)
{
	const size_t	size = array_size(elem);

	if (!validate_vector(elem[size - 1]))
		return (0);
	fill_vector(&obj->scale, elem[size - 1]);
	obj->transparency = ft_atof(elem[size - 2]);	
	obj->refractive = ft_atof(elem[size - 3]);	
	obj->reflective = ft_atof(elem[size - 4]);	
	obj->shininess = ft_atoi(elem[size - 5]);	
	obj->diffuse = ft_atof(elem[size - 6]);	
	obj->specular = ft_atof(elem[size - 7]);	
	if (!obj_validate_bonus(obj))
		return (0);
	return (1);
}

#endif

static int	sphere_add(t_obj *obj, char **elem)
{
	if (!str_isdouble(elem[2]))
		return (0);
	obj->type = t_sphere;
	fill_vector(&obj->pos, elem[1]);
	obj->radius = ft_atof(elem[2]);
	if ((obj->radius <= 0.0) || !fill_color(&obj->color, elem[3]))
		return (0);
	return (1);
}

static int	plane_add(t_obj *obj, char **elem)
{
	obj->type = t_plane;
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
	obj = ft_calloc(1, sizeof(t_obj));
	if (!obj)
		return (0);
	obj->pos.w = 1;
	if (id == ID_SPHERE)
		ret = sphere_add(obj, elem);
	else if (id == ID_PLANE)
		ret = plane_add(obj, elem);
	else if (id == ID_CYLINDER)
		ret = cylinder_add(obj, elem);
#ifdef BONUS
	if (ret)
		ret = obj_add_bonus_fields(obj, elem);
#endif
	if (!ret)
	{
		free(obj);
		return (0);
	}
	ft_void_arr_add(&scene->objs, obj);
	return (1);
}
