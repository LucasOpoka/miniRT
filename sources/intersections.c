/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:05:34 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/26 17:07:10 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

void	ft_add_intersection(t_void_arr *intersections, t_shape *shape, float t)
{
	t_intersection	*intr;

	if (!intersections->arr)
		return ;
	intr = malloc(sizeof(t_intersection));
	if (!intr)
		return (ft_free_void_arr(intersections));
	intr->shape = shape;
	intr->t = t;
	ft_void_arr_add(intersections, intr);
	
}

void	ft_sphere_intersection(t_vct O, t_vct D, t_shape *shape, t_void_arr *intersections)
{
	t_vct	center = ft_create_vct(0, 0, 0);
	t_vct	X = ft_vct_sub(&O, &center);
	float	a = ft_vct_dot(&D, &D);
	float	b = 2 * ft_vct_dot(&X, &D);
	float	c = ft_vct_dot(&X, &X) - (shape->radius * shape->radius);

	float discr = b * b - 4 * a * c;
	if (discr < 0)
		return ;
	ft_add_intersection(intersections, shape, (-b + sqrt(discr)) / (2 * a));
	ft_add_intersection(intersections, shape, (-b - sqrt(discr)) / (2 * a));
}

void	ft_plane_intersection(t_vct O, t_vct D, t_shape *shape, t_void_arr *intersections)
{
	float	denom = ft_vct_dot(&D, &shape->orientation);
	if (fabs(denom) < 0.0001)
		return ;
	t_vct diff = ft_vct_sub(&shape->position, &O);
	ft_add_intersection(intersections, shape, ft_vct_dot(&diff, &shape->orientation) / denom);
}

int	ft_check_caps(t_vct O, t_vct D, float t)
{
	float	x;
	float	z;

	x = O.x + D.x * t;
	z = O.z + D.z * t;
	return (x * x + z * z <= 1);
}

void	ft_intersect_caps(t_vct O, t_vct D, t_shape *shape, t_void_arr *intersections)
{
	float	t;

	if (fabs(D.y) < 0.001)
		return ;
	t = ((-shape->height / 2) - O.y) / D.y;
	if (ft_check_caps(O, D, t))
		ft_add_intersection(intersections, shape, t);
	t = ((shape->height / 2) - O.y) / D.y;
	if (ft_check_caps(O, D, t))
		ft_add_intersection(intersections, shape, t);
}

// The Raytracer Challenge p.177
void	ft_cylinder_intersection(t_vct O, t_vct D, t_shape *shape, t_void_arr *intersections)
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
			ft_add_intersection(intersections, shape, t[0]);
		y[1] = O.y + t[1] * D.y;
		if ((-half_h < y[1]) && (y[1] < half_h))
			ft_add_intersection(intersections, shape, t[1]);
	}
	ft_intersect_caps(O, D, shape, intersections);
}

void	ft_ray_to_shape_space(t_ray *shape_ray, t_ray *world_ray, t_shape *shape)
{	
	ft_vct_mtrx_mult(&shape_ray->O, &shape->world_to_shape, &world_ray->O);
	ft_vct_mtrx_mult(&shape_ray->D, &shape->world_to_shape, &world_ray->D);
}

void	ft_get_intersections(t_ray world_ray, t_scene *scene, t_void_arr *intersections)
{
	t_shape	*shape;
	t_ray	shape_ray;
	size_t	i;
	
	i = 0;
	while (i < scene->shapes.i && intersections->arr)
	{
		shape = (t_shape *) scene->shapes.arr[i++];
		ft_ray_to_shape_space(&shape_ray, &world_ray, shape);
	
		if (shape->type == t_sphere)
			ft_sphere_intersection(shape_ray.O, shape_ray.D, shape, intersections);
		if (shape->type == t_plane)
			ft_plane_intersection(shape_ray.O, shape_ray.D, shape, intersections);
		if (shape->type == t_cylinder)
			ft_cylinder_intersection(shape_ray.O, shape_ray.D, shape, intersections);
	}
}

t_intersection	*ft_closest_intersection(t_void_arr *intersections)
{
	t_intersection	*current;
	t_intersection	*closest;
	float			lowest_time;
	size_t			i;

	if (!intersections->arr)
		return (NULL);
	lowest_time = FLT_MAX;
	i = 0;
	closest = NULL;
	while (i < intersections->i)
	{
		current = (t_intersection *) intersections->arr[i];
		if (0 <= current->t && current->t < lowest_time)
		{
			lowest_time = current->t;
			closest = current;
		}
		i++;
	}
	return (closest);
}
