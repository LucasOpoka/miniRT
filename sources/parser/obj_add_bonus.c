/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_add_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:07:54 by atorma            #+#    #+#             */
/*   Updated: 2024/09/14 19:10:24 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

int			validate_orientation(t_vct v);
int			obj_add_bonus_fields(t_obj *obj, char **elem);

int	obj_add(t_scene *scene, char **elem, int id)
{
	t_obj	*obj;
	int		ret;

	ret = 0;
	printf("obj_add (BONUS) called\n");
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
	if (ret)
		ret = obj_add_bonus_fields(obj, elem);
	return (ret);
}
