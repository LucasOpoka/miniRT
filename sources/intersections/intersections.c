/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:05:34 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/18 17:53:10 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/miniRT.h"

void	ft_sphere_intersection(t_ray ray, t_obj *obj, t_xs *xs)
{
	t_vct	s_to_r;
	double	a;
	double	b;
	double	c;
	double	discr;

	s_to_r = ray.o;
	s_to_r.w = 0;
	a = ft_vct_dot(&ray.d, &ray.d);
	b = 2 * ft_vct_dot(&s_to_r, &ray.d);
	c = ft_vct_dot(&s_to_r, &s_to_r) - 1;
	discr = pow(b, 2) - 4 * a * c;
	if (discr < 0)
		return ;
	ft_add_intersection(xs, obj, (-b + sqrt(discr)) / (2 * a));
	ft_add_intersection(xs, obj, (-b - sqrt(discr)) / (2 * a));
}

void	ft_plane_intersection(t_ray ray, t_obj *obj, t_xs *xs)
{
	if (fabs(ray.d.y) < EPSILON)
		return ;
	ft_add_intersection(xs, obj, -ray.o.y / ray.d.y);
}

void	ft_ray_to_obj_space(t_ray *obj_ray, t_ray *world_ray, t_obj *obj)
{
	ft_vct_x_mtrx(&obj_ray->o, &obj->world_to_obj, &world_ray->o);
	ft_vct_x_mtrx(&obj_ray->d, &obj->world_to_obj, &world_ray->d);
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
		if (obj->type == t_cone)
			ft_cone_intersection(obj_ray, obj, xs);
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
