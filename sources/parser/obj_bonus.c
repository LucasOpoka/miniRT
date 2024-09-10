/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:37:32 by atorma            #+#    #+#             */
/*   Updated: 2024/09/10 18:40:28 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

/*
 *   object bonus fields after mandatory

	*   <specular> <diffuse> <shininess> <reflective> <refractive> <transparency> <scale vector>
 *   +7 fields
 */

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

int	obj_add_bonus_fields(t_obj *obj, char **elem)
{
	const size_t	size = array_size(elem);

	if (!validate_vector(elem[size - 1]))
		return (0);
	if (!validate_ratio(elem[size - 2], 0.0, 1.0))
		return (0);
	if (!validate_ratio(elem[size - 2], 0.0, 1.0))
		return (0);
	if ((!str_isdigit(elem[size - 5])) || ft_strlen(elem[size - 5]) >= 4)
		return (0);
	fill_vector(&obj->scale, elem[size - 1]);
	obj->transparency = ft_atof(elem[size - 2]);
	obj->refractive = ft_atof(elem[size - 3]);
	obj->reflective = ft_atof(elem[size - 4]);
	obj->shininess = ft_atoi(elem[size - 5]);
	obj->diffuse = ft_atof(elem[size - 6]);
	obj->specular = ft_atof(elem[size - 7]);
	return (obj_validate_bonus(obj));
}
