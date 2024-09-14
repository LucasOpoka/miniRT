/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:44:57 by atorma            #+#    #+#             */
/*   Updated: 2024/09/14 22:02:02 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <math.h>

void	double_set(double *f, double value)
{
	f[0] = value;
	f[1] = value;
	f[2] = value;
}

void	bounds_init(t_bounds *bounds)
{
	double_set(bounds->min, DBL_MAX);
	double_set(bounds->max, DBL_MIN);
}

void	swap_obj(uint32_t *obj_index, int i, int j)
{
	uint32_t	tmp;

	tmp = obj_index[i];
	obj_index[i] = obj_index[j];
	obj_index[j] = tmp;
}

void	centroids_calc(t_obj *obj)
{
	if (obj->type == t_triangle)
	{
		obj->centroid[0] = (obj->p1.x + obj->p1.x + obj->p1.x) * 0.3333f;
		obj->centroid[1] = (obj->p2.y + obj->p2.y + obj->p2.y) * 0.3333f;
		obj->centroid[2] = (obj->p3.z + obj->p3.z + obj->p3.z) * 0.3333f;
	}
	else
	{
		obj->centroid[0] = obj->pos.x;
		obj->centroid[1] = obj->pos.y;
		obj->centroid[2] = obj->pos.z;
	}
}

void	centroids_set(t_node *root, t_scene *scene)
{
	uint32_t	i;
	t_obj		*obj;

	i = 0;
	while (i < scene->objs.i)
	{
		obj = scene->objs.arr[i];
		if (obj->type != t_plane)
		{
			scene->bvh.i[root->count] = i;
			obj = scene->objs.arr[i];
			centroids_calc(obj);
			root->count++;
		}
		i++;
	}
}
