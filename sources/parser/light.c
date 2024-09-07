/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:07:41 by atorma            #+#    #+#             */
/*   Updated: 2024/09/05 20:59:02 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../includes/parser.h"
#include "../../libft/libft.h"

int	light_add_ambient(t_ambient *ambient, char **elem)
{
	if (!validate_ratio(elem[1], 0.0, 1.0))
		return (0);
	if (!fill_color(&ambient->color, elem[2]))
		return (0);
	ambient->intensity = ft_atof(elem[1]);
	return (1);
}

int	light_add_point(t_light *light, char **elem)
{
	if (!validate_vector(elem[1]))
		return (0);
	if (!validate_ratio(elem[2], 0.0, 1.0))
		return (0);
	light->type = t_point;
	fill_vector(&light->pos, elem[1]);
	light->intensity = ft_atof(elem[2]);
	if (!fill_color(&light->color, elem[3]))
		return (0);
#ifdef BONUS
	// For bonus lights have their direction vector in last (extra) element
	if (!validate_vector(elem[4]))
		return (0);
	fill_vector(&light->dir, elem[4]);
#endif
	return (1);
}

int	light_add(t_scene *scene, char **elem, int id)
{
	t_light	*light;
	int		ret;

	ret = 0;
	if (id == ID_AMBIENT)
		return (light_add_ambient(&scene->ambient, elem));
	light = ft_calloc(1, sizeof(t_light));
	if (!light)
		return (0);
	if (id == ID_LIGHT || id == ID_LIGHT_POINT)
		ret = light_add_point(light, elem);
	if (!ret)
	{
		free(light);
		return (0);
	}
	ft_void_arr_add(&scene->lights, light);
	return (ret);
}
