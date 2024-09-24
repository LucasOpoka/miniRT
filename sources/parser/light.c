/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:07:41 by atorma            #+#    #+#             */
/*   Updated: 2024/09/24 17:07:33 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../includes/parser.h"
#include "../../libft/libft.h"

int	light_add_ambient(t_ambient *ambient, char **elem)
{
	if (!validate_ratio(elem[1], 0.0, 1.0))
		return (parser_error("invalid ambient light ratio"));
	if (!fill_color(&ambient->color, elem[2]))
		return (parser_error("invalid ambient light color"));
	ambient->intensity = ft_atof(elem[1]);
	return (1);
}

int	light_add_point(t_light *light, char **elem)
{
	if (!validate_vector(elem[1]))
		return (parser_error("invalid light position"));
	if (!validate_ratio(elem[2], 0.0, 1.0))
		return (parser_error("invalid light ratio"));
	light->type = t_point;
	fill_vector(&light->pos, elem[1]);
	light->intensity = ft_atof(elem[2]);
	if (!fill_color(&light->color, elem[3]))
		return (parser_error("invalid light color"));
	return (1);
}

int	light_add(t_scene *scene, char **elem, int id)
{
	t_light	*light;
	int		ret;

	ret = 0;
	if (id == e_id_ambient)
		return (light_add_ambient(&scene->ambient, elem));
	light = ft_calloc(1, sizeof(t_light));
	if (!light || !ft_void_arr_add(&scene->lights, light))
		return (0);
	if (id == e_id_light || id == e_id_light_point)
		ret = light_add_point(light, elem);
	return (ret);
}
