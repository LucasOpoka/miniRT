/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:29:22 by atorma            #+#    #+#             */
/*   Updated: 2024/09/15 21:29:57 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <math.h>

void	sphere_bounds(t_bounds *bounds, t_obj *sp)
{
	const t_vct		scale = sp->scale;
	const double	radius = sp->radius;

	bounds->min[0] = scale.x * -radius + sp->pos.x;
	bounds->min[1] = scale.y * -radius + sp->pos.y;
	bounds->min[2] = scale.z * -radius + sp->pos.z;
	bounds->max[0] = scale.x * radius + sp->pos.x;
	bounds->max[1] = scale.y * radius + sp->pos.y;
	bounds->max[2] = scale.z * radius + sp->pos.z;
}

void	cylinder_bounds(t_bounds *bounds, t_obj *cy)
{
	const t_vct		scale = cy->scale;
	const double	radius = cy->radius * 2;
	const double	height = cy->height;

	bounds->min[0] = scale.x * -radius + cy->pos.x;
	bounds->min[1] = scale.y * -radius + cy->pos.y;
	bounds->min[2] = scale.z * -height + cy->pos.z;
	bounds->max[0] = scale.x * radius + cy->pos.x;
	bounds->max[1] = scale.y * radius + cy->pos.y;
	bounds->max[2] = scale.z * height + cy->pos.z;
}

void	cone_bounds(t_bounds *bounds, t_obj *cone)
{
	const t_vct		scale = cone->scale;
	const double	radius = cone->radius;
	const double	height = cone->height;

	bounds->min[0] = scale.x * -radius + cone->pos.x;
	bounds->min[1] = scale.y * -radius + cone->pos.y;
	bounds->min[2] = scale.z * -height + cone->pos.z;
	bounds->max[0] = scale.x * radius + cone->pos.x;
	bounds->max[1] = scale.y * radius + cone->pos.y;
	bounds->max[2] = scale.z * height + cone->pos.z;
}

void	triangle_bounds(t_bounds *bounds, t_obj *tri)
{
	const t_vct	scale = tri->scale;

	bounds->min[0] = scale.x * +fmin(fmin(tri->p1.x, tri->p2.x), tri->p3.x);
	bounds->min[1] = scale.y * +fmin(fmin(tri->p1.y, tri->p2.y), tri->p3.y);
	bounds->min[2] = scale.z * +fmin(fmin(tri->p1.z, tri->p2.z), tri->p3.z);
	bounds->max[0] = scale.x * +fmax(fmax(tri->p1.x, tri->p2.x), tri->p3.x);
	bounds->max[1] = scale.y * +fmax(fmax(tri->p1.y, tri->p2.y), tri->p3.y);
	bounds->max[2] = scale.z * +fmax(fmax(tri->p1.z, tri->p2.z), tri->p3.z);
}
