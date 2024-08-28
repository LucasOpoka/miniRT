/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lopoka@student.hive.fi>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:55:43 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/28 17:12:27 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

void	ft_show_img(t_mrt *mrt, t_scene *scene)
{
	t_ray		world_ray;
	t_clr		color;
	int			pixel_x;
	int			pixel_y;
	t_void_arr	intersections;

	// Init camera
	ft_init_camera(&scene->camera);
	ft_set_camera_matrices(&scene->camera);
	ft_set_all_shapes_matrices(scene);

	pixel_y = 0;
	while (pixel_y < CANV_HGHT)
	{
		pixel_x = 0;
		while (pixel_x < CANV_WDTH)
		{	
			ft_init_void_arr(&intersections);
			ft_pixel_to_ray(&world_ray, pixel_x, pixel_y, &scene->camera);
			ft_get_intersections(world_ray, scene, &intersections);
			color = ft_get_color(&world_ray, scene, 3, &intersections);
			mlx_put_pixel(mrt->img, pixel_x++, pixel_y, ft_clr_to_int(color));
			ft_free_void_arr(&intersections);
		}
		pixel_y++;
	}
	mlx_image_to_window(mrt->mlx, mrt->img, 0, 0);
}
