
#ifndef BVH_H
# define BVH_H

#include "miniRT.h"

t_node	*bvh_build(t_void_arr *shapes);
void	bvh_intersect(t_ray ray, t_scene *scene, t_node *root, uint32_t	index,
		t_intersects *intersect);
#endif
