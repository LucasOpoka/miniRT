/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:52:19 by atorma            #+#    #+#             */
/*   Updated: 2024/09/19 04:16:20 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <math.h>

double			aabb_raycast(t_ray ray, t_bounds bounds);

void			ft_ray_to_obj_space(t_ray *obj_ray, t_ray *world_ray,
					t_obj *obj);
void			ft_get_intrscs(t_ray world_ray, t_scene *scene, t_xs *xs);
void			ft_sphere_intersection(t_ray obj_ray, t_obj *obj, t_xs *xs);
void			ft_plane_intersection(t_ray ray, t_obj *obj, t_xs *xs);
void			ft_cylinder_intersection(t_ray obj_ray, t_obj *obj, t_xs *xs);

void	intersects_obj(t_ray ray, t_scene *scene, t_node *node, t_xs *xs)
{
	t_obj		*obj;
	t_ray		obj_ray;
	uint32_t	i;
	void (*func[5])(t_ray , t_obj *, t_xs *);

	i = 0;
	func[t_sphere] = ft_sphere_intersection;
	func[t_plane] = ft_plane_intersection;
	func[t_cylinder] = ft_cylinder_intersection;
	func[t_triangle] = ft_triangle_intersection;
	func[t_cone] = ft_cone_intersection;
	while (i < node->count)
	{
		obj = scene->objs.arr[scene->bvh.i[node->first_index + i]];
		ft_ray_to_obj_space(&obj_ray, &ray, obj);
		func[obj->type](obj_ray, obj, xs);
		i++;
	}
}

void	add_planes(t_ray ray, t_scene *scene, t_xs *xs)
{
	t_obj		*obj;
	t_void_arr	*objs;
	t_ray		obj_ray;
	uint32_t	i;

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

/*
 * dist[0] must contain the shorter distance
 */

static void	swap_nodes(double *dist, t_node **n1, t_node **n2)
{
	double	tmp;
	t_node	*tmp_node;

	if (dist[0] > dist[1])
	{
		tmp = dist[0];
		dist[0] = dist[1];
		dist[1] = tmp;
		tmp_node = *n1;
		*n1 = *n2;
		*n2 = tmp_node;
	}
}

static t_node	*intersects_box(t_ray ray, t_node *root, t_node *curr,
		t_stack *s)
{
	t_node	*left;
	t_node	*right;
	double	dist[2];

	left = &root[curr->left];
	right = &root[curr->left + 1];
	dist[0] = aabb_raycast(ray, left->bounds);
	dist[1] = aabb_raycast(ray, right->bounds);
	swap_nodes(dist, &left, &right);
	if (dist[0] == DBL_MAX)
	{
		if (s->ptr == 0)
			return (NULL);
		return (s->stack[--s->ptr]);
	}
	if (dist[1] != DBL_MAX)
		s->stack[s->ptr++] = right;
	return (left);
}

/*
 * Efficient BVH traversal using temporary stack
 * https://graphics.cg.uni-saarland.de/papers/perard-2017-gpce.pdf
 */

void	bvh_intersect(t_ray ray, t_scene *scene, t_xs *xs)
{
	t_node	*node;
	t_stack	s;

	node = &scene->bvh.root[0];
	s.ptr = 0;
	ray.rd.x = 1.0 / ray.d.x;
	ray.rd.y = 1.0 / ray.d.y;
	ray.rd.z = 1.0 / ray.d.z;
	while (node)
	{
		if (node->count > 0)
		{
			intersects_obj(ray, scene, node, xs);
			if (s.ptr == 0)
				break ;
			node = s.stack[--s.ptr];
			continue ;
		}
		node = intersects_box(ray, scene->bvh.root, node, &s);
	}
	add_planes(ray, scene, xs);
	heap_sort_xs(xs);
}

/*
 * Recursive version, this can have bad performance depending on camera position
void	bvh_intersect(t_ray ray, t_scene *scene, uint32_t index, t_xs *xs)
{
	t_node	*node;

	node = &scene->bvh_root[index];
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
