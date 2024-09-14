/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:45:30 by atorma            #+#    #+#             */
/*   Updated: 2024/09/14 17:41:02 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include "../includes/parser.h"
#include "../includes/ppm.h"
#include "../libft/libft.h"

int	scene_init(t_scene *scene)
{
	ft_init_void_arr(&scene->lights);
	ft_init_void_arr(&scene->objs);
	return (1);
}

static void	obj_free(t_scene *scene)
{
	uint32_t	i;
	t_obj		*obj;

	i = 0;
	while (i < scene->objs.i)
	{
		obj = scene->objs.arr[i];
		ppm_matrix_free(&obj->txtr);
		ppm_matrix_free(&obj->bump);
		i++;
	}
}

void	scene_free(t_scene *scene)
{
	obj_free(scene);
	ft_free_void_arr(&scene->lights);
	ft_free_void_arr(&scene->objs);
	free(scene->bvh.root);
	free(scene->bvh.i);
}
