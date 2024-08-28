
#include "../../includes/miniRT.h"
#include "../../libft/libft.h"
#include <math.h>


uint32_t used = 1;

void	node_print_entry(t_node *node);
void	node_print_full(t_node *node, t_void_arr *shapes, int axis, float split_pos);

void	node_min_max(float *to_min, float *to_max, float *min, float *max);
float	node_cost(t_node *node);

void	sphere_bounds(float *min, float *max, t_shape *sphere);
void	cylinder_bounds(float *min, float *max, t_shape *cylinder);
void	shape_bounds_update(t_node *node, t_shape *shape);

void	float_set(float *f, float value)
{
	f[0] = value;
	f[1] = value;
	f[2] = value;
}

void	bvh_update_bounds(t_node *root, uint32_t index, t_scene *scene)
{
	t_node	    *node = &root[index];
	t_shape	    *shape;
	size_t	    i;

	i = 0;
	float_set(node->min, FLT_MAX);
	float_set(node->max, FLT_MIN);

	while (i < node->count)
	{
		shape = scene->shapes.arr[scene->bvh_index[node->first_index+ i]];
		shape_bounds_update(node, shape);
		i++;
	}
}


//Plane is split along the longest axis, not used anymore this is bad
float bvh_split_plane_old(t_node *node)
{
	float	split_pos;
	float	extent[3];
	int	axis;

	axis = 0;
	extent[0] = node->max[0] - node->min[0];
	extent[1] = node->max[1] - node->min[1];
	extent[2] = node->max[2] - node->min[2];
	if (extent[1] > extent[0])
		axis = 1;
	if (extent[2] > extent[axis])
		axis = 2;
	split_pos = node->min[axis] + extent[axis] * 0.5f;
	return (split_pos);
}


void	swap_qsort(uint32_t *shape_index, int i, int j)
{
	uint32_t    tmp;

	tmp = shape_index[i];
	shape_index[i] = shape_index[j];
	shape_index[j] = tmp;
}

float	find_best_split(t_node *node, int *axis, float *split_pos, t_scene *scene);

void	bvh_subdivide(t_node *root, uint32_t index, t_scene *scene)
{
	t_node	*node = &root[index];
	int	axis;
	float	split_pos;
	//float	extent[3];

	/*
	if (node->count <= 2)
		return ;
	split_pos = bvh_split_plane(node, extent, &axis);
	printf("split_pos: %f\n", split_pos);
	printf("split_axis: %d\n", axis);
	*/
	float no_split_cost = node_cost(node);	
	float split_cost = find_best_split(node, &axis, &split_pos, scene);
	if (split_cost >= no_split_cost)
		return ;

	printf("no_split_cost: %f, split_cost: %f, split_pos: %f, axis: %d\n",
			no_split_cost, split_cost, split_pos, axis);
	uint32_t    i = node->first_index;
	uint32_t    j = node->count + i - 1;
	uint32_t    left_count = 0;
	uint32_t    right_count = 0;
	while (i <= j)
	{
		t_shape *shape = scene->shapes.arr[scene->bvh_index[i]];
		if (shape->centroid[axis] < split_pos)
		{
			left_count++;
			i++;
		}
		else
		{
			swap_qsort(scene->bvh_index, i, j--);
			right_count++;
		}
	}
	if (!left_count || !right_count)
		return ;
	printf("left_count: %d, right_count: %d\n", left_count, right_count);
	int left_index = used++;
	int right_index  = used++;
	root[left_index].first_index = node->first_index;
	root[left_index].count = left_count;
	root[right_index].first_index = i;
	root[right_index].count = right_count;
	node->left = left_index;
	node->right = right_index;
	node->count = 0;
	//node->right can later be removed as it is not used anymore

	bvh_update_bounds(root, left_index, scene);
	bvh_update_bounds(root, right_index, scene);
	bvh_subdivide(root, left_index, scene);
	bvh_subdivide(root, right_index, scene);
}

long long	time_ms(void);

t_node	*bvh_build(t_scene *scene)
{
	uint32_t    i;
	t_node	    *root;
	uint32_t    *bvh_index;

	root = ft_calloc(1, (scene->shapes.i * 2 * sizeof(t_node)));
	bvh_index = ft_calloc(1, (scene->shapes.i * sizeof(uint32_t)));
	if (!root || !bvh_index)
	{
		free(root);
		free(bvh_index);
		return (NULL);
	}
	scene->bvh_root = root;
	scene->bvh_index = bvh_index;
	root->count = scene->shapes.i;
	i = 0;
	while (i < root->count)
	{
		scene->bvh_index[i] = i;
		t_shape *shape = scene->shapes.arr[i];
		shape->centroid[0] = shape->position.x;
		shape->centroid[1] = shape->position.y;
		shape->centroid[2] = shape->position.z;
		i++;
	}
	long long ms_start = time_ms();
	bvh_update_bounds(root, 0, scene);
	bvh_subdivide(root, 0, scene);
	long long ms_end = time_ms();
	printf("bhv_build took: %lldms\n", ms_end - ms_start);
	return (root);
}
