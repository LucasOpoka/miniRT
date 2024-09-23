/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:29:22 by atorma            #+#    #+#             */
/*   Updated: 2024/09/23 17:09:03 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <math.h>

void	sphere_bounds(t_bounds *bounds, t_obj *sp)
{
	const double	radius = sp->scale.x;

	bounds->min[0] = -radius + sp->pos.x;
	bounds->min[1] = -radius + sp->pos.y;
	bounds->min[2] = -radius + sp->pos.z;
	bounds->max[0] = radius + sp->pos.x;
	bounds->max[1] = radius + sp->pos.y;
	bounds->max[2] = radius + sp->pos.z;
}

void	cylinder_bounds(t_bounds *bounds, t_obj *cy)
{
	const double	radius = fmax(cy->scale.x, cy->scale.y);

	bounds->min[0] = -radius + cy->pos.x;
	bounds->min[1] = -radius + cy->pos.y;
	bounds->min[2] = -radius + cy->pos.z;
	bounds->max[0] = radius + cy->pos.x;
	bounds->max[1] = radius + cy->pos.y;
	bounds->max[2] = radius + cy->pos.z;
}

void	cone_bounds(t_bounds *bounds, t_obj *cone)
{
	const double	radius = fmax(cone->scale.x, cone->scale.y);

	bounds->min[0] = -radius + cone->pos.x;
	bounds->min[1] = -radius + cone->pos.y;
	bounds->min[2] = -radius + cone->pos.z;
	bounds->max[0] = radius + cone->pos.x;
	bounds->max[1] = radius + cone->pos.y;
	bounds->max[2] = radius + cone->pos.z;
}

void	triangle_bounds(t_bounds *bounds, t_obj *tri)
{
	const t_vct	scale = tri->scale;

	bounds->min[0] = scale.x * fmin(fmin(tri->p1.x, tri->p2.x), tri->p3.x);
	bounds->min[1] = scale.y * fmin(fmin(tri->p1.y, tri->p2.y), tri->p3.y);
	bounds->min[2] = scale.z * fmin(fmin(tri->p1.z, tri->p2.z), tri->p3.z);
	bounds->max[0] = scale.x * fmax(fmax(tri->p1.x, tri->p2.x), tri->p3.x);
	bounds->max[1] = scale.y * fmax(fmax(tri->p1.y, tri->p2.y), tri->p3.y);
	bounds->max[2] = scale.z * fmax(fmax(tri->p1.z, tri->p2.z), tri->p3.z);
}
