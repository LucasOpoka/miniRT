/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lopoka@student.hive.fi>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:55:43 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/19 17:22:34 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

void	ft_check_closest_shape(t_shape *shape, float t, float t_min, float t_max, float *t_closest, t_shape **shape_closest)
{
	if ((t >= t_min && t <= t_max) && t < *t_closest)
	{
		*t_closest = t;
		*shape_closest = shape;
	}
}

// P - C = D*t + X
// Where C is a center point of a shape that we hit and X equals O-C. 

void	ft_closest_intersection(t_vct O, t_vct D, t_scene *scene, float t_min, float t_max, float *t_closest, t_shape **shape_closest)
{
	//X = CO

	t_shape	*shape;
	size_t	i;
	
	i = 0;
	while (i < scene->shapes.i)
	{
		shape = (t_shape *) scene->shapes.arr[i++];
		if (shape->type == t_sphere)
		{
			t_vct	X = ft_vct_sub(O, shape->position);
			float	a = ft_vct_dot(D, D);
			float	b = 2 * ft_vct_dot(X, D);
			float	c = ft_vct_dot(X, X) - (shape->radius * shape->radius);

			float discr = b * b - 4 * a * c;
			if (discr < 0)
				continue ;
			ft_check_closest_shape(shape, (-b + sqrt(discr)) / (2 * a), t_min, t_max, t_closest, shape_closest);
			ft_check_closest_shape(shape, (-b - sqrt(discr)) / (2 * a), t_min, t_max, t_closest, shape_closest);
		}
		if (shape->type == t_plane)
		{
			float	denom = ft_vct_dot(D, shape->orientation);
			if (fabs(denom) < 0.0001)
				continue ;
			ft_check_closest_shape(shape, ft_vct_dot(ft_vct_sub(shape->position, O), shape->orientation) / denom, t_min, t_max, t_closest, shape_closest);
		}
	}
}

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
