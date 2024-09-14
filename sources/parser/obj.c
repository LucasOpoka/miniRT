/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:07:54 by atorma            #+#    #+#             */
/*   Updated: 2024/09/14 19:01:13 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

int			validate_orientation(t_vct v);

int	sphere_add(t_obj *obj, char **elem)
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

int	plane_add(t_obj *obj, char **elem)
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

int	cylinder_add(t_obj *obj, char **elem)
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
