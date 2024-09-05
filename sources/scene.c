/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:45:30 by atorma            #+#    #+#             */
/*   Updated: 2024/09/05 20:45:38 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/miniRT.h"
#include "../includes/parser.h"

int	scene_init(t_scene *scene)
{
	ft_init_void_arr(&scene->lights);
	ft_init_void_arr(&scene->objs);

	return (1);
}

void	scene_free(t_scene *scene)
{
	ft_free_void_arr(&scene->lights);
	ft_free_void_arr(&scene->objs);
	free(scene->bvh.root);
	free(scene->bvh.i);
}
