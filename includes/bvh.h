/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:52:41 by atorma            #+#    #+#             */
/*   Updated: 2024/08/28 17:27:36 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

#include "miniRT.h"


t_node	*bvh_build(t_scene *scene);
void	bvh_intersect(t_ray ray, t_scene *scene, uint32_t index, t_intersects *intersect);
void	bvh_intersect_ordered(t_ray ray, t_scene* scene, t_intersects *intersect);
#endif
