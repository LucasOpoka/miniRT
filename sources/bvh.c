
#include "../includes/miniRT.h"
#include "../libft/libft.h"
#include <math.h>


uint32_t    shape_index[256];

uint32_t used = 1;

void	set_bounds(float *vct, float val, t_vct scale, t_vct pos)
{
	vct[0] = scale.x * val + pos.x;
	vct[1] = scale.y * val + pos.y;
	vct[2] = scale.z * val + pos.z;
}

void	sphere_bounds(t_node *node, t_shape *sphere)
{
	set_bounds(node->min, -sphere->radius, sphere->scale, sphere->position);
	set_bounds(node->max, sphere->radius, sphere->scale, sphere->position);
}

void	sphere_bounds_fmax(t_node *node, t_shape *sphere)
{
	float	min[3];
	float	max[3];
	set_bounds(min, -sphere->radius, sphere->scale, sphere->position);
	set_bounds(max, sphere->radius, sphere->scale, sphere->position);
	
	node->min[0] = fminf(node->min[0], min[0]);
	node->min[1] = fminf(node->min[1], min[1]);
	node->min[2] = fminf(node->min[2], min[2]);

	node->max[0] = fmaxf(node->max[0], max[0]);
	node->max[1] = fmaxf(node->max[1], max[1]);
	node->max[2] = fmaxf(node->max[2], max[2]);
}

void	bvh_update_bounds(t_node *root, uint32_t index, t_void_arr *shapes)
{
	t_node	*node = &root[index];
	size_t	i;

	i = 0;

	uint32_t    first = node->first_index;
	t_shape *shape = (t_shape *)shapes->arr[shape_index[first + i]];
	sphere_bounds(node, shape);

	i++;
	while (i < node->count)
	{
		shape = (t_shape *)shapes->arr[shape_index[first + i]];
		if (shape->type != t_sphere)
		{
			i++;
			continue;
		}
		sphere_bounds_fmax(node, shape);
		i++;
	}
}

void	print_node(t_node *node, t_void_arr *shapes, int axis, float split_pos)
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

int bvh_split_plane(t_node *node, float *extent, int *axis_out)
{
	float	split_pos;
	int	axis;

	axis = 0;
	extent[0] = node->max[0] - node->min[0];
	extent[1] = node->max[1] - node->min[1];
	extent[2] = node->max[2] - node->min[2];
	if (extent[1] > extent[0])
		axis = 1;
	if (extent[2] > extent[axis])
		axis = 2;
	*axis_out = axis;
	split_pos = node->min[axis] + extent[axis] * 0.5f;
	return (split_pos);
}

void	swap_qsort(int i, int j)
{
	uint32_t    tmp;

	tmp = shape_index[i];
	shape_index[i] = shape_index[j];
	shape_index[j] = tmp;
}

void	bvh_subdivide(t_node *root, uint32_t index, t_void_arr *shapes)
{
	t_node	*node = &root[index];
	int	axis;
	float	split_pos;
	float	extent[3];
	float	centroid[3];

	if (node->count <= 2)
		return ;
	split_pos = bvh_split_plane(node, extent, &axis);
	printf("split_pos: %f\n", split_pos);
	printf("split_axis: %d\n", axis);

	uint32_t    i = node->first_index;
	uint32_t    j = node->count + i - 1;
	uint32_t    left_count = 0;
	uint32_t    right_count = 0;
	while (i <= j)
	{
		t_shape *shape = (t_shape *)shapes->arr[shape_index[i]];
		centroid[0] = shape->position.x;
		centroid[1] = shape->position.y;
		centroid[2] = shape->position.z;
		if (centroid[axis] < split_pos)
		{
			left_count++;
			i++;
		}
		else
		{
			swap_qsort(i, j--);
			right_count++;
		}
	}
	print_node(node, shapes, axis, split_pos);
	//check empty
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
	bvh_update_bounds(root, left_index, shapes);
	bvh_update_bounds(root, right_index, shapes);
	bvh_subdivide(root, left_index, shapes);
	bvh_subdivide(root, right_index, shapes);
}

t_node	*bvh_build(t_void_arr *shapes)
{
	t_node	*root = ft_calloc(1, (shapes->i * 2 * sizeof(t_node)));

	if (!root)
		return (NULL);
	root->count = shapes->i;

	uint32_t i = 0;
	while (i < shapes->i)
	{
		shape_index[i] = i;
		i++;
	}
	bvh_update_bounds(root, 0, shapes);
	bvh_subdivide(root, 0, shapes);
	return (root);
}

void	print_node_small(t_node *node)
{
	printf("PRINT_NODE: count: %u\n", node->count);
	printf("node->first_index: %d\n", node->first_index);
	printf("aabb_min.x: %f\n", node->min[0]);
	printf("aabb_min.y: %f\n", node->min[1]);
	printf("aabb_min.z: %f\n", node->min[2]);
}

static int aabb_raycast(t_ray ray, float bmin[3], float bmax[3])
{
    t_vct   rd;
    rd.x = 1.0 / ray.D.x;
    rd.y = 1.0 / ray.D.y;
    rd.z = 1.0 / ray.D.z;
    float t1 = (bmin[0] - ray.O.x) * rd.x;
    float t2 = (bmax[0] - ray.O.x) * rd.x;
    float t3 = (bmin[1] - ray.O.y) * rd.y;
    float t4 = (bmax[1] - ray.O.y) * rd.y;
    float t5 = (bmin[2] - ray.O.z) * rd.z;
    float t6 = (bmax[2] - ray.O.z) * rd.z;

    float tmin = fmaxf(fmaxf(fminf(t1, t2), fminf(t3, t4)), fminf(t5, t6));
    float tmax = fminf(fminf(fmaxf(t1, t2), fmaxf(t3, t4)), fmaxf(t5, t6));

    // if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
    if (tmax < 0)
	return (0);
    // if tmin > tmax, ray doesn't intersect AABB
    if (tmin > tmax)
	return (0);
    return (1);
    //return (tmin < tmax);
}

void	ft_ray_to_shape_space(t_ray *shape_ray, t_ray *world_ray, t_shape *shape);

void	ft_get_intersections(t_ray world_ray, t_scene *scene, t_intersects *intersect);
void	ft_sphere_intersection(t_vct O, t_vct D, t_shape *shape, t_intersects *intersect);

void	bvh_intersect(t_ray ray, t_scene *scene, t_node *root, uint32_t	index,
		t_intersects *intersect)
{
	t_node	*node = &root[index];
	t_ray	shape_ray;

	if (!aabb_raycast(ray, node->min, node->max))
		return ;
	if (node->count > 0)
	{
		uint32_t    first = node->first_index;
		uint32_t    i = 0;
		while (i < node->count)
		{
			t_shape *shape = (t_shape *)scene->shapes.arr[shape_index[first + i]];
			ft_ray_to_shape_space(&shape_ray, &ray, shape);
	
			ft_sphere_intersection(shape_ray.O, shape_ray.D, shape, intersect);
			i++;
		}
		return ;
	}
	bvh_intersect(ray, scene, root, node->left, intersect);
	bvh_intersect(ray, scene, root, node->left + 1, intersect);
}
