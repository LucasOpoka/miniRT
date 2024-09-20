/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:06:54 by atorma            #+#    #+#             */
/*   Updated: 2024/09/20 18:22:42 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <pthread.h>
#include <sys/time.h>
#include <time.h>

int		threads_init(t_mrt *mrt, t_scene *scene);
void	threads_wait(t_mrt *mrt);
void	threads_join(t_mrt *mrt);
void	close_hook(void *ptr);

static void	render_mandatory(t_mrt *mrt, t_scene *scene, t_xs *xs)
{
	t_ray		ray;
	t_clr		color;
	uint32_t	y;
	uint32_t	x;

	y = 0;
	while (y < mrt->img->height)
	{
		x = 0;
		while (x < mrt->img->width)
		{
			ft_pixel_to_ray(&ray, x, y, &scene->cam);
			color = ft_final_color(&ray, scene, 5, xs);
			mlx_put_pixel(mrt->img, x, y, ft_clr_to_int(color));
			x++;
		}
		y++;
	}
}

static void	render_image(t_mrt *mrt, t_scene *scene)
{
	t_xs	xs[2];

	if (!ft_init_xs(&xs[0]) || !ft_init_xs(&xs[1]))
	{
		printf("Error\nintersection array allocation failed\n");
		ft_free_xs(xs);
		ft_free_xs(&xs[1]);
		close_hook(mrt);
		return ;
	}
	render_mandatory(mrt, scene, xs);
	ft_free_xs(&xs[0]);
	ft_free_xs(&xs[1]);
}

void	render(t_mrt *mrt, t_scene *scene)
{
	const mlx_image_t	*img = mrt->img;

	ft_bzero(img->pixels, img->width * img->height * sizeof(int));
	ft_init_cam(&scene->cam);
	ft_set_cam_matrices(&scene->cam);
	ft_set_all_objs_matrices(scene);
	mlx_image_to_window(mrt->mlx, mrt->img, 0, 0);
	render_image(mrt, scene);
}
