/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_add_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:07:54 by atorma            #+#    #+#             */
/*   Updated: 2024/09/17 20:35:45 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

int	validate_orientation(t_vct v);
int	obj_add_bonus_fields(t_obj *obj, char **elem);

/*
 * triangle
 * <p1> <p2> <p3> <scale vector> <color> <bonus fields>
 */

int	valid_triangle(char **elem)
{
	size_t	i;

	i = 1;
	while (i <= 4)
	{
		if (!validate_vector(elem[i++]))
			return (0);
	}
	return (1);
}

int	triangle_add(t_obj *obj, char **elem)
{
	t_vct	normal;

	if (!valid_triangle(elem))
		return (0);
	obj->type = t_triangle;
	fill_vector(&obj->p1, elem[1]);
	fill_vector(&obj->p2, elem[2]);
	fill_vector(&obj->p3, elem[3]);
	if (!fill_color(&obj->color, elem[4]))
		return (0);
	obj->p1.w = 1;
	obj->p2.w = 1;
	obj->p3.w = 1;
	obj->e1 = ft_vct_sub(&obj->p2, &obj->p1);
	obj->e2 = ft_vct_sub(&obj->p3, &obj->p1);
	ft_vct_cross_prod(&normal, &obj->e2, &obj->e1);
	normal.w = 0;
	ft_vct_norm(&normal);
	obj->orientation = ft_create_vct(0, 0, 0);
	return (1);
}

int	cone_add(t_obj *obj, char **elem)
{
	double	radius;
	double	height;

	obj->type = t_cone;
	fill_vector(&obj->pos, elem[1]);
	fill_vector(&obj->orientation, elem[2]);
	radius = ft_atof(elem[3]);
	height = ft_atof(elem[4]);
	obj->scale = ft_create_vct(radius, height, radius);
	if (radius <= 0.0 || height <= 0.0)
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
	if (!obj || !ft_void_arr_add(&scene->objs, obj))
		return (0);
	obj->scale = ft_create_vct(1, 1, 1);
	obj->pos.w = 1;
	if (id == e_id_sphere)
		ret = sphere_add(obj, elem);
	else if (id == e_id_plane)
		ret = plane_add(obj, elem);
	else if (id == e_id_cylinder)
		ret = cylinder_add(obj, elem);
	else if (id == e_id_cone)
		ret = cone_add(obj, elem);
	else if (id == e_id_triangle)
		ret = triangle_add(obj, elem);
	if (ret)
		ret = obj_add_bonus_fields(obj, elem);
	if (!ret)
		printf("obj_add bonus err: %d\n", obj->type);
	return (ret);
}
