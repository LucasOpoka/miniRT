/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:37:32 by atorma            #+#    #+#             */
/*   Updated: 2024/09/23 17:58:10 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"
#include "../../../includes/parser.h"

int			str_isalpha_lower(const char *s);

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
	if (obj->shininess > 5000 || obj->refractive > 3)
		return (0);
	return (1);
}

static int	obj_load_ppm(t_ppm *obj_ppm, const char *file)
{
	char	path[128];

	if (ft_strcmp(file, "none") == 0)
		return (1);
	if (ft_strlen(file) > 64 || !str_isalpha_lower(file))
		return (0);
	ft_strlcpy(path, "./ppms/", sizeof(path));
	ft_strlcat(path, file, sizeof(path));
	ft_strlcat(path, ".ppm", sizeof(path));
	if (!ppm_load(path, obj_ppm))
		return (0);
	return (1);
}

static int	obj_patterns(t_obj *obj, const char *texture)
{
	if (ft_strcmp("checkers", texture) == 0)
		obj->ptrn = ft_ptrn(ft_checkers, 2, 2);
	else if (ft_strcmp("rings", texture) == 0)
		obj->ptrn = ft_ptrn(ft_rings, 25, 25);
	else if (ft_strcmp("arches", texture) == 0)
		obj->ptrn = ft_ptrn(ft_arches, 25, 25);
	return (obj->ptrn.ptrn_func != NULL);
}

int	obj_add_bonus_ppm(t_obj *obj, char **elem)
{
	const size_t	size = array_size(elem);
	const char		*texture = elem[size - 3];
	const char		*bump_map = elem[size - 2];
	char			*modifier;

	if (obj_patterns(obj, texture))
		return (1);
	modifier = elem[size - 1];
	if (!obj_load_ppm(&obj->txtr, texture))
		return (0);
	if (!obj_load_ppm(&obj->bump, bump_map))
		return (0);
	if (obj->bump.colors)
	{
		if (!str_isdouble(modifier))
			return (0);
		obj->bump_modifier = ft_atof(modifier);
		if (obj->bump_modifier < 0 || obj->bump_modifier > 100)
			return (0);
	}
	return (1);
}

/*
 *   object bonus fields
 *   <specular> <diffuse> <shininess>
 *   <reflective> <refractive> <transparency>
 *   <texture ppm / pattern> <bump ppm> <bump modifier>
 *   +9 fields to mandatory
 */

int	obj_add_bonus_fields(t_obj *obj, char **elem)
{
	const size_t	size = array_size(elem) - 3;

	if (!obj_add_bonus_ppm(obj, elem))
		return (0);
	if (!validate_ratio(elem[size - 1], 0.0, 1.0))
		return (0);
	if (!validate_ratio(elem[size - 2], 0.0, 100.0))
		return (0);
	if ((!str_isdigit(elem[size - 4])) || ft_strlen(elem[size - 4]) >= 4)
		return (0);
	obj->transparency = ft_atof(elem[size - 1]);
	obj->refractive = ft_atof(elem[size - 2]);
	obj->reflective = ft_atof(elem[size - 3]);
	obj->shininess = ft_atoi(elem[size - 4]);
	obj->diffuse = ft_atof(elem[size - 5]);
	obj->specular = ft_atof(elem[size - 6]);
	return (obj_validate_bonus(obj));
}
