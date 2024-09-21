/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:52:41 by atorma            #+#    #+#             */
/*   Updated: 2024/09/21 19:38:30 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# include "miniRT.h"

# define BVH_MAX_NODES 10240
# define BVH_MIN_CHILDREN 1

t_node	*bvh_build(t_scene *scene);
void	bvh_intersect(t_ray ray, t_scene *scene, t_xs *xs);

#endif
