
#include "../../includes/miniRT.h"
#include <math.h>

void	node_min_max(float *to_min, float *to_max, float *min, float *max)
{
	to_min[0] = fminf(to_min[0], min[0]);
	to_min[1] = fminf(to_min[1], min[1]);
	to_min[2] = fminf(to_min[2], min[2]);

	to_max[0] = fmaxf(to_max[0], max[0]);
	to_max[1] = fmaxf(to_max[1], max[1]);
	to_max[2] = fmaxf(to_max[2], max[2]);
}

float	node_cost(t_node *node)
{
	float	extent[3];
	float	area;

	extent[0] = node->max[0] - node->min[0];
	extent[1] = node->max[1] - node->min[1];
	extent[2] = node->max[2] - node->min[2];
	area = extent[0] * extent[1] + extent[1] * extent[2] + extent[2] * extent[0];
	return (node->count * area);
}

void	node_print_entry(t_node *node)
{
	printf("PRINT_NODE: count: %u\n", node->count);
	printf("node->first_index: %d\n", node->first_index);
	printf("aabb_min.x: %f\n", node->min[0]);
	printf("aabb_min.y: %f\n", node->min[1]);
	printf("aabb_min.z: %f\n", node->min[2]);
}

/*
void	node_print_full(t_node *node, t_void_arr *shapes, int axis, float split_pos)
{
	float	centroid[3];
	uint32_t    i = node->first_index;
	uint32_t    j = node->count + i - 1;
	printf("PRINT_NODE count: %u\n", node->count);
	while (i <= j)
	{
		t_shape *shape = (t_shape *)shapes->arr[shape_index[i]];
		centroid[0] = shape->position.x;
		centroid[1] = shape->position.y;
		centroid[2] = shape->position.z;
		if (centroid[axis] < split_pos)
			printf("LEFT: %u\n", i);
		else
			printf("RIGHT: %u\n", i);
		i++;
	}
}
*/
