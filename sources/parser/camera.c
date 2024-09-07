/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:07:18 by atorma            #+#    #+#             */
/*   Updated: 2024/08/24 18:07:19 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../includes/parser.h"
#include "../../libft/libft.h"

int			validate_orientation(t_vct v);

static int	valid_fov(char *fov)
{
	size_t	fov_len;
	double	fov_val;

	fov_len = ft_strlen(fov);
	if (!str_isdigit(fov) || (fov_len > 3))
		return (0);
	fov_val = ft_atof(fov);
	if (fov_val < 0.0 || fov_val > 180.0)
		return (0);
	return (1);
}

int	cam_add(t_scene *scene, char **elem)
{
	if (!validate_vector(elem[1]) || !validate_vector(elem[2]))
		return (0);
	if (!valid_fov(elem[3]))
		return (0);
	fill_vector(&scene->cam.pos, elem[1]);
	fill_vector(&scene->cam.dir, elem[2]);
	scene->cam.pos.w = 1;
	scene->cam.dir.w = 0;
	scene->cam.fov = ft_atof(elem[3]);
	if (!validate_orientation(scene->cam.dir))
		return (0);
	return (1);
}
