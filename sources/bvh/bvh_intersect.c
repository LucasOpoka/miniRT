/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:52:19 by atorma            #+#    #+#             */
/*   Updated: 2024/09/01 15:53:23 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <math.h>

double aabb_raycast(t_ray ray, double bmin[3], double bmax[3]);

void	ft_ray_to_obj_space(t_ray *obj_ray, t_ray *world_ray, t_obj *obj);
void	ft_get_intersections(t_ray world_ray, t_scene *scene, t_xs *xs);
void	ft_sphere_intersection(t_ray obj_ray, t_obj *obj, t_xs *xs);
void	ft_cylinder_intersection(t_ray obj_ray, t_obj *obj, t_xs *xs);

void	intersects_obj(t_ray ray, t_scene *scene, t_node *node, t_xs *xs)
{
	t_obj	    *obj;
	t_ray	    obj_ray;
	uint32_t    i;

	i = 0;
	while (i < node->count)
	{
		obj = scene->objs.arr[scene->bvh_index[node->first_index + i]];
		ft_ray_to_obj_space(&obj_ray, &ray, obj);

		if (obj->type == t_sphere)
			ft_sphere_intersection(obj_ray, obj, xs);
		if (obj->type == t_cylinder)
			ft_cylinder_intersection(obj_ray, obj, xs);
		i++;
	}
}

void	ft_plane_intersection(t_ray ray, t_obj *obj, t_xs *xs);
void	add_planes(t_ray ray, t_scene *scene, t_xs *xs)
{
	t_obj	    *obj;
	t_void_arr  *objs;
	t_ray	    obj_ray;
	uint32_t    i;

	i = 0;
	objs = &scene->objs;
	while (i < objs->i)
	{
		obj = objs->arr[i];
		if (obj->type == t_plane)
		{
			ft_ray_to_obj_space(&obj_ray, &ray, obj);
			ft_plane_intersection(obj_ray, obj, xs);
		}
		i++;
	}
}

void	swap_float_node(double *f1, double *f2, t_node **n1, t_node **n2)
{
	double	tmp;
	t_node	*tmp_node;

	tmp = *f1;
	*f1 = *f2;
	*f2 = tmp;
	tmp_node = *n1;
	*n1 = *n2;
	*n2 = tmp_node;
}

t_node *intersects_node(t_ray ray, t_node *root, t_node *curr, t_stack *s)
{
	t_node	*left;
	t_node	*right;
	double	d1;
	double	d2;

	left = &root[curr->left];
	right = &root[curr->left + 1];
	d1 = aabb_raycast(ray, left->bounds.min, left->bounds.max);
	d2 = aabb_raycast(ray, right->bounds.min, right->bounds.max);
	if (d1 > d2)
		swap_float_node(&d1, &d2, &left, &right);
	if (d1 == DBL_MAX) //Miss
	{
		if (s->ptr == 0)
			return (NULL);
		return (s->stack[--s->ptr]);
	}
	if (d2 != DBL_MAX)
		s->stack[s->ptr++] = right;
	return (left);
}

int	ft_xs_compare(const void *a, const void *b);
void	bvh_intersect_ordered(t_ray ray, t_scene* scene, t_xs *xs)
{
	t_node	    *node = &scene->bvh_root[0];
	t_stack	    s;

	s.ptr = 0;
	ray.rd.x = 1.0 / ray.D.x;
	ray.rd.y = 1.0 / ray.D.y;
	ray.rd.z = 1.0 / ray.D.z;
	while (node)
	{
		if (node->count > 0)
		{
			intersects_obj(ray, scene, node, xs);
			if (s.ptr == 0)
				break;
			node = s.stack[--s.ptr];
			continue;
		}
		node = intersects_node(ray, scene->bvh_root, node, &s);
	}
	add_planes(ray, scene, xs);
	if (xs->arr && xs->i > 0)
		qsort(xs->arr, xs->i, sizeof(t_intersection), ft_xs_compare);
}

/*
void	bvh_intersect(t_ray ray, t_scene *scene, uint32_t index, t_xs *xs)
{
	t_node	*node = &scene->bvh_root[index];

	if (aabb_raycast(ray, node->min, node->max) == DBL_MAX)
		return ;
	if (node->count > 0)
	{
		intersects_obj(ray, scene, node, xs);
		return ;
	}
	bvh_intersect(ray, scene, node->left, xs);
	bvh_intersect(ray, scene, node->left + 1, xs);
}
*/
