
#include "../includes/miniRT.h"
#include "../libft/libft.h"
#include <math.h>

typedef	struct	t_aabb
{
	float	x;
	float	y;
	float	z;
}	t_aabb;

typedef	struct	t_node
{
	t_aabb		aabb_min;
	t_aabb		aabb_max;
	uint32_t	left;
	uint32_t	right;
	uint32_t	is_leaf;
	uint32_t	is_prim;
	uint32_t	count;
}	t_node;

void	bvh_update_bounds(t_node *node, t_void_arr *shapes)
{
	size_t	i;

	i = 0;

	t_shape *shape = (t_shape *)shapes->arr[i];
	node->aabb_min.x = shape->position.x;
	node->aabb_min.y = shape->position.y;
	node->aabb_min.z = shape->position.z;

	node->aabb_max.x = shape->position.x;
	node->aabb_max.y = shape->position.y;
	node->aabb_max.z = shape->position.z;

	i++;
	while (i < node->count)
	{
		shape = (t_shape *)shapes->arr[i];
		if (shape->type != t_sphere)
		{
			i++;
			continue;
		}

		node->aabb_min.x = fminf(node->aabb_min.x, shape->position.x);
		node->aabb_min.y = fminf(node->aabb_min.y, shape->position.y);
		node->aabb_min.z = fminf(node->aabb_min.z, shape->position.z);

		node->aabb_max.x = fmaxf(node->aabb_max.x, shape->position.x);
		node->aabb_max.y = fmaxf(node->aabb_max.y, shape->position.y);
		node->aabb_max.z = fmaxf(node->aabb_max.z, shape->position.z);
		i++;
	}
	printf("aabb_min.x: %f\n", node->aabb_min.x);
	printf("aabb_min.y: %f\n", node->aabb_min.y);
	printf("aabb_min.z: %f\n", node->aabb_min.z);

	printf("aabb_max.x: %f\n", node->aabb_max.x);
	printf("aabb_max.y: %f\n", node->aabb_max.y);
	printf("aabb_max.z: %f\n", node->aabb_max.z);
}

void	bvh_subdivide(t_node *node)
{
	int		axis = 0;
	float	extent[3];

	extent[0] = node->aabb_max.x - node->aabb_min.x;
	extent[1] = node->aabb_max.y - node->aabb_min.y;
	extent[2] = node->aabb_max.z - node->aabb_min.z;
	if (extent[1] > extent[0])
		axis = 1;
	if (extent[2] > extent[axis])
		axis = 2;
	float split_pos = node->aabb_min[axis] + extent[axis] * 0.5;
	printf("split_pos: %f\n", split_pos);
}
t_node	*bvh_build(t_void_arr *shapes)
{
	t_node	*root = ft_calloc(1, (shapes->i * sizeof(t_node)));

	root->count = shapes->i;
	root->is_prim = 0;

	bhv_update_bounds(root, shapes);
	bhv_subdivide(root);
	return (root);
}

void	bhv_test(t_void_arr *shapes)
{
	t_node *root = bhv_build(shapes);
	free(root);
}
