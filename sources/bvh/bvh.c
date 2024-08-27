
#include "../../includes/miniRT.h"
#include "../../libft/libft.h"
#include <math.h>


uint32_t used = 1;
uint32_t    shape_index[256];

void	node_print_entry(t_node *node);
void	node_print_full(t_node *node, t_void_arr *shapes, int axis, float split_pos);

void	node_min_max(t_node *node, float *min, float *max);

void	sphere_bounds(float *min, float *max, t_shape *sphere);
void	cylinder_bounds(float *min, float *max, t_shape *cylinder);
void	shape_bounds_update(t_node *node, t_shape *shape);

//int aabb_raycast(t_ray ray, float bmin[3], float bmax[3]);
float aabb_raycast(t_ray ray, float bmin[3], float bmax[3]);

void	bvh_update_bounds(t_node *root, uint32_t index, t_void_arr *shapes)
{
	t_node	*node = &root[index];
	t_shape	*shape;
	size_t	i;

	i = 0;

	uint32_t    first = node->first_index;

	node->min[0] = FLT_MAX;
	node->min[1] = FLT_MAX;
	node->min[2] = FLT_MAX;

	node->max[0] = FLT_MIN;
	node->max[1] = FLT_MIN;
	node->max[2] = FLT_MIN;
	while (i < node->count)
	{
		shape = (t_shape *)shapes->arr[shape_index[first + i]];
		shape_bounds_update(node, shape);
		i++;
	}
}


//Plane is split along the longest axis
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
		if (shape->centroid[axis] < split_pos)
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
		t_shape *shape = shapes->arr[i];
		shape->centroid[0] = shape->position.x;
		shape->centroid[1] = shape->position.y;
		shape->centroid[2] = shape->position.z;
		i++;
	}
	bvh_update_bounds(root, 0, shapes);
	bvh_subdivide(root, 0, shapes);
	return (root);
}



void	ft_ray_to_shape_space(t_ray *shape_ray, t_ray *world_ray, t_shape *shape);

void	ft_get_intersections(t_ray world_ray, t_scene *scene, t_intersects *intersect);
void	ft_sphere_intersection(t_vct O, t_vct D, t_shape *shape, t_intersects *intersect);
void	ft_cylinder_intersection(t_vct O, t_vct D, t_shape *shape, t_intersects *intersect);

void	intersects_shape(t_ray ray, t_scene *scene, t_node *node, t_intersects *intersect)
{
	t_shape	    *shape;
	t_ray	    s_ray;
	uint32_t    i;

	i = 0;
	while (i < node->count)
	{
		shape = scene->shapes.arr[shape_index[node->first_index + i]];
		ft_ray_to_shape_space(&s_ray, &ray, shape);

		if (shape->type == t_sphere)
			ft_sphere_intersection(s_ray.O, s_ray.D, shape, intersect);
		if (shape->type == t_cylinder)
			ft_cylinder_intersection(s_ray.O, s_ray.D, shape, intersect);
		i++;
	}
}

void	swap_float_node(float *f1, float *f2, t_node **n1, t_node **n2)
{
	float	tmp;
	t_node	*tmp_node;

	tmp = *f1;
	*f1 = *f2;
	*f2 = tmp;
	tmp_node = *n1;
	*n1 = *n2;
	*n2 = tmp_node;
}

t_node *intersects_node(t_ray ray, t_node *root, t_node *curr, t_stack *s)
{
	t_node	*left;
	t_node	*right;
	float	d1;
	float	d2;

	left = &root[curr->left];
	right = &root[curr->left + 1];
	d1 = aabb_raycast(ray, left->min, left->max);
	d2 = aabb_raycast(ray, right->min, right->max);
	if (d1 > d2)
		swap_float_node(&d1, &d2, &left, &right);
	if (d1 == FLT_MAX) //Miss
	{
		if (s->ptr == 0)
			return (NULL);
		return (s->stack[--s->ptr]);
	}
	if (d2 != FLT_MAX)
		s->stack[s->ptr++] = right;
	return (left);
}

void	bvh_intersect_ordered(t_ray ray, t_scene* scene, t_intersects *intersect)
{
	t_node	    *node = &scene->bhv_root[0];
	t_stack	    s;

	s.ptr = 0;
	while (node)
	{
		if (node->count > 0)
		{
			intersects_shape(ray, scene, node, intersect);
			if (s.ptr == 0)
				break;
			node = s.stack[--s.ptr];
			continue;
		}
		node = intersects_node(ray, scene->bhv_root, node, &s);
	}
}

void	bvh_intersect(t_ray ray, t_scene *scene, uint32_t index, t_intersects *intersect)
{
	t_node	*node = &scene->bhv_root[index];

	if (aabb_raycast(ray, node->min, node->max) == FLT_MAX)
		return ;
	if (node->count > 0)
	{
		intersects_shape(ray, scene, node, intersect);
		return ;
	}
	bvh_intersect(ray, scene, node->left, intersect);
	bvh_intersect(ray, scene, node->left + 1, intersect);
}
