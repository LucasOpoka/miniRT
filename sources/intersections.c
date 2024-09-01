/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:05:34 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/01 15:26:56 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

int ft_intersect_compare(const void *a, const void *b);

void	ft_sphere_intersection(t_ray ray, t_shape *shape, t_xs *xs)
{
	t_vct	center = ft_create_vct(0, 0, 0);
	center.w = 1;
	t_vct	X = ft_vct_sub(&ray.O, &center);
	double	a = ft_vct_dot(&ray.D, &ray.D);
	double	b = 2 * ft_vct_dot(&X, &ray.D);
	double	c = ft_vct_dot(&X, &X) - (shape->radius * shape->radius);

	double discr = b * b - 4 * a * c;
	if (discr < 0)
		return ;
	ft_add_intersection(xs, shape, (-b + sqrt(discr)) / (2 * a));
	ft_add_intersection(xs, shape, (-b - sqrt(discr)) / (2 * a));
}

void	ft_plane_intersection(t_ray ray, t_shape *shape, t_xs *xs)
{
	if (fabs(ray.D.y) < EPSILON)
		return ;
	ft_add_intersection(xs, shape, -ray.O.y / ray.D.y);
}

int	ft_check_caps(t_ray ray, double t)
{
	double	x;
	double	z;

	x = ray.O.x + ray.D.x * t;
	z = ray.O.z + ray.D.z * t;
	return (x * x + z * z <= 1);
}

void	ft_intersect_caps(t_ray ray, t_shape *shape, t_xs *xs)
{
	double	t;

	if (fabs(ray.D.y) < EPSILON)
		return ;
	t = ((-shape->height / 2) - ray.O.y) / ray.D.y;
	if (ft_check_caps(ray, t))
		ft_add_intersection(xs, shape, t);
	t = ((shape->height / 2) - ray.O.y) / ray.D.y;
	if (ft_check_caps(ray, t))
		ft_add_intersection(xs, shape, t);
}

// The Raytracer Challenge p.177
void	ft_cylinder_intersection(t_ray ray, t_shape *shape, t_xs *xs)
{
	double	a;
	double	b;
	double	c;
	double	disc;
	double	t[2];
	double	tmp;
	double	y[2];
	double	half_h;

	a = ray.D.x * ray.D.x + ray.D.z * ray.D.z;
	b = 2 * ray.O.x * ray.D.x + 2 * ray.O.z * ray.D.z;
	c = ray.O.x * ray.O.x + ray.O.z * ray.O.z - 1;
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

		y[0] = ray.O.y + t[0] * ray.D.y;
		if ((-half_h < y[0]) && (y[0] < half_h))
			ft_add_intersection(xs, shape, t[0]);
		y[1] = ray.O.y + t[1] * ray.D.y;
		if ((-half_h < y[1]) && (y[1] < half_h))
			ft_add_intersection(xs, shape, t[1]);
	}
	ft_intersect_caps(ray, shape, xs);
}

void	ft_ray_to_shape_space(t_ray *shape_ray, t_ray *world_ray, t_shape *shape)
{	
	ft_vct_mtrx_mult(&shape_ray->O, &shape->world_to_shape, &world_ray->O);
	ft_vct_mtrx_mult(&shape_ray->D, &shape->world_to_shape, &world_ray->D);
}

void	ft_get_intersections(t_ray world_ray, t_scene *scene, t_xs *xs)
{
	t_shape	*shape;
	t_ray	shape_ray;
	size_t	i;
	
	i = 0;
	while (i < scene->shapes.i && xs->arr)
	{
		shape = (t_shape *) scene->shapes.arr[i++];
		ft_ray_to_shape_space(&shape_ray, &world_ray, shape);
	
		if (shape->type == t_sphere)
			ft_sphere_intersection(shape_ray, shape, xs);
		if (shape->type == t_plane)
			ft_plane_intersection(shape_ray, shape, xs);
		if (shape->type == t_cylinder)
			ft_cylinder_intersection(shape_ray, shape, xs);
	}
	// Sort the intersections
	if (xs->arr)
		qsort(xs->arr, xs->i, sizeof(t_intersection), ft_intersect_compare);
}

t_intersection	*ft_closest_intersection(t_xs *xs)
{
	t_intersection	*current;
	t_intersection	*closest;
	double			lowest_time;
	size_t			i;

	if (!xs->arr)
		return (NULL);
	lowest_time = DBL_MAX;
	i = 0;
	closest = NULL;
	while (i < xs->i)
	{
		current = &xs->arr[i];
		if (0 <= current->t && current->t < lowest_time)
		{
			lowest_time = current->t;
			closest = current;
		}
		i++;
	}
	return (closest);
}

// Sorting stuff
int ft_intersect_compare(const void *a, const void *b)
{
	double	t_a;
	double	t_b; 

	t_a = ((t_intersection *) a)->t;
	t_b = ((t_intersection *) b)->t;

	return ((t_a > t_b) - (t_a < t_b));
}
