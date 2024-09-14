/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:52:41 by atorma            #+#    #+#             */
/*   Updated: 2024/09/14 22:16:33 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

#include "miniRT.h"

# define BVH
# define BVH_MAX_NODES 10 * 1024
# define BVH_MIN_CHILDREN 1

t_node	*bvh_build(t_scene *scene);
void	bvh_intersect(t_ray ray, t_scene* scene, t_xs *xs);
//void	bvh_intersect(t_ray ray, t_scene *scene, uint32_t index, t_xs *xs);
#endif
