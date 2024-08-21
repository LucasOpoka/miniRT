/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:05:34 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/21 15:51:10 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

// P - C = D*t + X
// Where C is a center point of a shape that we hit and X equals O-C. 
// X = CO

void	ft_check_closest_shape(t_shape *shape, float t, float t_min, float t_max, float *t_closest, t_shape **shape_closest)
{
	if ((t >= t_min && t <= t_max) && t < *t_closest)
	{
		*t_closest = t;
		*shape_closest = shape;
	}
}

void	ft_sphere_intersection(t_vct O, t_vct D, t_shape *shape, float t_min, float t_max, float *t_closest, t_shape **shape_closest)
{
	t_vct	X = ft_vct_sub(O, ft_create_vct(0, 0, 0));
	float	a = ft_vct_dot(D, D);
	float	b = 2 * ft_vct_dot(X, D);
	float	c = ft_vct_dot(X, X) - (shape->radius * shape->radius);

	float discr = b * b - 4 * a * c;
	if (discr < 0)
		return ;
	ft_check_closest_shape(shape, (-b + sqrt(discr)) / (2 * a), t_min, t_max, t_closest, shape_closest);
	ft_check_closest_shape(shape, (-b - sqrt(discr)) / (2 * a), t_min, t_max, t_closest, shape_closest);
}

void	ft_plane_intersection(t_vct O, t_vct D, t_shape *shape, float t_min, float t_max, float *t_closest, t_shape **shape_closest)
{
	float	denom = ft_vct_dot(D, shape->orientation);
	if (fabs(denom) < 0.0001)
		return ;
	ft_check_closest_shape(shape, ft_vct_dot(ft_vct_sub(shape->position, O), shape->orientation) / denom, t_min, t_max, t_closest, shape_closest);
}

void	ft_closest_intersection(t_vct O, t_vct D, t_scene *scene, float t_min, float t_max, float *t_closest, t_shape **shape_closest)
{
	t_shape	*shape;
	size_t	i;
	t_vct	NO;
	t_vct	ND;
	
	i = 0;
	while (i < scene->shapes.i)
	{
		shape = (t_shape *) scene->shapes.arr[i++];

		ft_vct_mtrx_mult(&NO, shape->world_to_shape, O);
		ft_vct_mtrx_mult(&ND, shape->world_to_shape, D);
	
		if (shape->type == t_sphere)
			ft_sphere_intersection(NO, ND, shape, t_min, t_max, t_closest, shape_closest);
		if (shape->type == t_plane)
			ft_plane_intersection(NO, ND, shape, t_min, t_max, t_closest, shape_closest);
	}
}
