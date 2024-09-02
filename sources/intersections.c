/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:05:34 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/01 19:39:27 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

void	ft_sphere_intersection(t_ray ray, t_obj *obj, t_xs *xs)
{
	t_vct	center = ft_create_vct(0, 0, 0);
	center.w = 1;
	t_vct	X = ft_vct_sub(&ray.O, &center);
	double	a = ft_vct_dot(&ray.D, &ray.D);
	double	b = 2 * ft_vct_dot(&X, &ray.D);
	double	c = ft_vct_dot(&X, &X) - (obj->radius * obj->radius);

	double	discr = b * b - 4 * a * c;
	if (discr < 0)
		return ;
	ft_add_intersection(xs, obj, (-b + sqrt(discr)) / (2 * a));
	ft_add_intersection(xs, obj, (-b - sqrt(discr)) / (2 * a));
}

void	ft_plane_intersection(t_ray ray, t_obj *obj, t_xs *xs)
{
	if (fabs(ray.D.y) < EPSILON)
		return ;
	ft_add_intersection(xs, obj, -ray.O.y / ray.D.y);
}

int	ft_check_caps(t_ray ray, double t)
{
	double	x;
	double	z;

	x = ray.O.x + ray.D.x * t;
	z = ray.O.z + ray.D.z * t;
	return (x * x + z * z <= 1);
}

void	ft_intersect_caps(t_ray ray, t_obj *obj, t_xs *xs)
{
	double	t;

	if (fabs(ray.D.y) < EPSILON)
		return ;
	t = ((-obj->height / 2) - ray.O.y) / ray.D.y;
	if (ft_check_caps(ray, t))
		ft_add_intersection(xs, obj, t);
	t = ((obj->height / 2) - ray.O.y) / ray.D.y;
	if (ft_check_caps(ray, t))
		ft_add_intersection(xs, obj, t);
}

// The Raytracer Challenge p.177
void	ft_cylinder_intersection(t_ray ray, t_obj *obj, t_xs *xs)
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
		half_h = obj->height / 2;
		y[0] = ray.O.y + t[0] * ray.D.y;
		if ((-half_h < y[0]) && (y[0] < half_h))
			ft_add_intersection(xs, obj, t[0]);
		y[1] = ray.O.y + t[1] * ray.D.y;
		if ((-half_h < y[1]) && (y[1] < half_h))
			ft_add_intersection(xs, obj, t[1]);
	}
	ft_intersect_caps(ray, obj, xs);
}

void	ft_ray_to_obj_space(t_ray *obj_ray, t_ray *world_ray, t_obj *obj)
{
	ft_vct_mtrx_mult(&obj_ray->O, &obj->world_to_obj, &world_ray->O);
	ft_vct_mtrx_mult(&obj_ray->D, &obj->world_to_obj, &world_ray->D);
}

void	ft_get_intersections(t_ray world_ray, t_scene *scene, t_xs *xs)
{
	t_obj	*obj;
	t_ray	obj_ray;
	size_t	i;

	i = 0;
	while (i < scene->objs.i && xs->arr)
	{
		obj = (t_obj *) scene->objs.arr[i++];
		ft_ray_to_obj_space(&obj_ray, &world_ray, obj);
		if (obj->type == t_sphere)
			ft_sphere_intersection(obj_ray, obj, xs);
		if (obj->type == t_plane)
			ft_plane_intersection(obj_ray, obj, xs);
		if (obj->type == t_cylinder)
			ft_cylinder_intersection(obj_ray, obj, xs);
	}
	heap_sort_xs(xs);
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
