/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:05:34 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/23 14:22:39 by lucas            ###   ########.fr       */
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
	t_vct	center = ft_create_vct(0, 0, 0);
	t_vct	X = ft_vct_sub(&O, &center);
	float	a = ft_vct_dot(&D, &D);
	float	b = 2 * ft_vct_dot(&X, &D);
	float	c = ft_vct_dot(&X, &X) - (shape->radius * shape->radius);

	float discr = b * b - 4 * a * c;
	if (discr < 0)
		return ;
	ft_check_closest_shape(shape, (-b + sqrt(discr)) / (2 * a), t_min, t_max, t_closest, shape_closest);
	ft_check_closest_shape(shape, (-b - sqrt(discr)) / (2 * a), t_min, t_max, t_closest, shape_closest);
}

void	ft_plane_intersection(t_vct O, t_vct D, t_shape *shape, float t_min, float t_max, float *t_closest, t_shape **shape_closest)
{
	float	denom = ft_vct_dot(&D, &shape->orientation);
	if (fabs(denom) < 0.0001)
		return ;
	t_vct diff = ft_vct_sub(&shape->position, &O);
	ft_check_closest_shape(shape, ft_vct_dot(&diff, &shape->orientation) / denom, t_min, t_max, t_closest, shape_closest);
}

int	ft_check_caps(t_vct O, t_vct D, float t)
{
	float	x;
	float	z;

	x = O.x + D.x * t;
	z = O.z + D.z * t;
	return (x * x + z * z <= 1);
}

void	ft_intersect_caps(t_vct O, t_vct D, t_shape *shape, float t_min, float t_max, float *t_closest, t_shape **shape_closest)
{
	float	t;

	if (fabs(D.y) < 0.001)
		return ;
	t = ((-shape->height / 2) - O.y) / D.y;
	if (ft_check_caps(O, D, t))	
		ft_check_closest_shape(shape, t, t_min, t_max, t_closest, shape_closest);
	t = ((shape->height / 2) - O.y) / D.y;
	if (ft_check_caps(O, D, t))	
		ft_check_closest_shape(shape, t, t_min, t_max, t_closest, shape_closest);	
}

// The Raytracer Challenge p.177
void	ft_cylinder_intersection(t_vct O, t_vct D, t_shape *shape, float t_min, float t_max, float *t_closest, t_shape **shape_closest)
{
	float	a;
	float	b;
	float	c;
	float	disc;
	float	t[2];
	float	tmp;
	float	y[2];
	float	half_h;

	a = D.x * D.x + D.z * D.z;
	b = 2 * O.x * D.x + 2 * O.z * D.z;
	c = O.x * O.x + O.z * O.z - 1;
	disc = b * b - 4 * a * c;

	if (disc >= 0)
	{
		disc = sqrt(disc);
		t[0] = (-b - disc) / (2 * a);
		t[1] = (-b + disc) / (2 * a);

		if (t[0] > t[1])
		{
			tmp = t[0];
			t[0] = t[1];
			t[1] = tmp;
		}

		half_h = shape->height / 2;

		y[0] = O.y + t[0] * D.y;
		if ((-half_h < y[0]) && (y[0] < half_h))
			ft_check_closest_shape(shape, t[0], t_min, t_max, t_closest, shape_closest);
		y[1] = O.y + t[1] * D.y;
		if ((-half_h < y[1]) && (y[1] < half_h))
			ft_check_closest_shape(shape, t[1], t_min, t_max, t_closest, shape_closest);
	}
	ft_intersect_caps(O, D, shape, t_min, t_max, t_closest, shape_closest);
}

void	ft_ray_to_shape_space(t_ray *shape_ray, t_ray *world_ray, t_shape *shape)
{	
	ft_vct_mtrx_mult(&shape_ray->O, &shape->world_to_shape, &world_ray->O);
	ft_vct_mtrx_mult(&shape_ray->D, &shape->world_to_shape, &world_ray->D);
}

void	ft_closest_intersection(t_ray world_ray, t_scene *scene, float t_min, float t_max, float *t_closest, t_shape **shape_closest)
{
	t_shape	*shape;
	t_ray	shape_ray;
	size_t	i;
	
	i = 0;
	while (i < scene->shapes.i)
	{
		shape = (t_shape *) scene->shapes.arr[i++];
		ft_ray_to_shape_space(&shape_ray, &world_ray, shape);
	
		if (shape->type == t_sphere)
			ft_sphere_intersection(shape_ray.O, shape_ray.D, shape, t_min, t_max, t_closest, shape_closest);
		if (shape->type == t_plane)
			ft_plane_intersection(shape_ray.O, shape_ray.D, shape, t_min, t_max, t_closest, shape_closest);
		if (shape->type == t_cylinder)
			ft_cylinder_intersection(shape_ray.O, shape_ray.D, shape, t_min, t_max, t_closest, shape_closest);
	}
}
