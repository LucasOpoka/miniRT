/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:58:32 by atorma            #+#    #+#             */
/*   Updated: 2024/09/14 19:02:10 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

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
	obj->pos.w = 1;
	if (id == e_id_sphere)
		ret = sphere_add(obj, elem);
	else if (id == e_id_plane)
		ret = plane_add(obj, elem);
	else if (id == e_id_cylinder)
		ret = cylinder_add(obj, elem);
	return (ret);
}
