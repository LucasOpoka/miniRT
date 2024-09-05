/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:05:34 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/05 14:37:54 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/miniRT.h"

void	ft_sphere_intersection(t_ray ray, t_obj *obj, t_xs *xs)
{
	t_vct	s_to_r;
	double	a;
	double	b;
	double	c;
	double	discr;

	s_to_r = ray.O;
	s_to_r.w = 0;
	a = ft_vct_dot(&ray.D, &ray.D);
	b = 2 * ft_vct_dot(&s_to_r, &ray.D);
	c = ft_vct_dot(&s_to_r, &s_to_r) - (obj->radius * obj->radius);
	discr = pow(b, 2) - 4 * a * c;
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

void	ft_ray_to_obj_space(t_ray *obj_ray, t_ray *world_ray, t_obj *obj)
{
	ft_vct_x_mtrx(&obj_ray->O, &obj->world_to_obj, &world_ray->O);
	ft_vct_x_mtrx(&obj_ray->D, &obj->world_to_obj, &world_ray->D);
}

void	ft_get_intrscs(t_ray world_ray, t_scene *scene, t_xs *xs)
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
		if (obj->type == t_triangle)
			ft_triangle_intersection(obj_ray, obj, xs);
	}
	heap_sort_xs(xs);
}

t_intrsc	*ft_hit(t_xs *xs)
{
	t_intrsc	*current;
	t_intrsc	*hit;
	double		lowest_time;
	size_t		i;

	if (!xs->arr)
		return (NULL);
	lowest_time = DBL_MAX;
	i = 0;
	hit = NULL;
	while (i < xs->i)
	{
		current = &xs->arr[i];
		if (0 <= current->t && current->t < lowest_time)
		{
			lowest_time = current->t;
			hit = current;
		}
		i++;
	}
	return (hit);
}
