/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lopoka@student.hive.fi>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:55:43 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/20 21:10:21 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

void	ft_show_img(t_mrt *mrt)
{
	t_vct		O;
	t_vct		D;
	t_clr		color;
	int			pixel_x;
	int			pixel_y;

	// Test scene
	t_scene scene = get_test_scene();

	// Init camera
	ft_init_camera(&scene.camera);
	ft_set_camera_matrices(&scene.camera);
	ft_set_all_shapes_matrices(&scene);

	// Closest shape variables
	float		t_closest;
	t_shape		*shape_closest;


	pixel_y = 0;
	while (pixel_y < CANV_HGHT)
	{
		pixel_x = 0;
		while (pixel_x < CANV_WDTH)
		{
			t_closest = FLT_MAX;
			shape_closest = NULL;
			
			D = ft_pixel_to_ray(pixel_x, pixel_y, scene.camera, &O);
			ft_closest_intersection(O, D, &scene, 1, 100000, &t_closest, &shape_closest);
			color = ft_get_color(O, D, &scene, 1, 100000, 3, t_closest, shape_closest);
			mlx_put_pixel(mrt->img, pixel_x++, pixel_y, ft_clr_to_int(color));
		}
		pixel_y++;
	}

	ft_free_void_arr(&scene.shapes);
	ft_free_void_arr(&scene.lights);

	mlx_image_to_window(mrt->mlx, mrt->img, 0, 0);
}
