/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lopoka@student.hive.fi>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:55:43 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/03 17:15:44 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

void	ft_show_img(t_mrt *mrt, t_scene *scene)
{
	t_ray	world_ray;
	t_clr	color;
	int		pixel_x;
	int		pixel_y;
	t_xs	xs;

	ft_init_cam(&scene->cam);
	ft_set_cam_matrices(&scene->cam);
	ft_set_all_objs_matrices(scene);
	pixel_y = 0;
	while (pixel_y < CANV_HGHT)
	{
		pixel_x = 0;
		while (pixel_x < CANV_WDTH)
		{
			ft_init_xs(&xs);
			ft_pixel_to_ray(&world_ray, pixel_x, pixel_y, &scene->cam);
			ft_get_intrscs(world_ray, scene, &xs);
			color = ft_final_color(&world_ray, scene, 5, &xs);
			mlx_put_pixel(mrt->img, pixel_x++, pixel_y, ft_clr_to_int(color));
			ft_free_xs(&xs);
		}
		pixel_y++;
	}
	mlx_image_to_window(mrt->mlx, mrt->img, 0, 0);
}
