/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:16:04 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/02 17:21:05 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef STRUCTS_H
# define STRUCTS_H

#include "worker.h"

typedef double	t_mtrx2[2][2];
typedef double	t_mtrx3[3][3];
typedef double	t_mtrx4[4][4];


typedef struct s_mrt
{
	mlx_t				*mlx;
	mlx_image_t			*img;
	pthread_t			threads[MAX_THREADS + 1];
	size_t				thread_count;
	int					threads_finished;
	pthread_mutex_t		lock;
	pthread_cond_t		notify;
	pthread_cond_t		complete;
	int					do_render;
	int				exit;
}	t_mrt;

typedef struct	t_bounds
{
	float		min[3];
	float		max[3];
}	t_bounds;

typedef	struct	t_node
{
	float		min[3];
	float		max[3];
	uint32_t	left;
	uint32_t	first_index;
	uint32_t	count;
}	t_node;

typedef	struct	t_split
{
	float	    cost;
	float	    pos;
	uint32_t    axis;
}	t_split;

typedef struct	t_stack
{
    t_node	*stack[64];
    uint32_t	ptr;
}   t_stack;

typedef struct s_vct
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_vct;

typedef struct s_clr
{
	double	r;
	double	g;
	double	b;
}	t_clr;

typedef struct s_obj
{
	float	centroid[3];
	int		type;
	t_vct	pos;
	double	radius;
	double	height;
	t_clr	color;
	double	specular;
	double	diffuse;
	int		shininess;
	double	reflective;
	double	refractive;
	double	transparency;
	t_vct	orientation;
	t_vct	scale;
	t_mtrx4	obj_to_world;
	t_mtrx4	world_to_obj;
	t_mtrx4	normal_to_world;
}	t_obj;

typedef struct s_light
{
	int		type;
	double	intensity;
	t_vct	pos;
	t_vct	dir;
	t_clr	color;
}	t_light;

typedef enum e_light_type
{
	t_point,
	t_diral
}	t_light_type;

typedef enum e_obj_type
{
	t_sphere,
	t_plane,
	t_cylinder
}	t_obj_type;

typedef struct s_void_arr
{
	void	**arr;
	size_t	size;
	size_t	curr;
	size_t	i;
	size_t	to_add;
}	t_void_arr;

typedef struct s_cam
{
	t_vct	pos;
	t_vct	dir;
	double	fov;
	double	pixel_size;
	double	half_wdth;
	double	half_hght;
	t_mtrx4	world_to_cam;
	t_mtrx4	cam_to_world;
}	t_cam;

typedef	struct	t_ambient
{
	double	intensity;
	t_clr	color;
}	t_ambient;


typedef	struct s_scene
{
	t_cam	cam;
	t_ambient	ambient;
	t_void_arr	lights;
	t_void_arr	objs;
	t_node		*bvh_root;
	uint32_t	*bvh_index;
}	t_scene;

typedef	struct s_ray
{
	t_vct	O;
	t_vct	D;
	t_vct	rd;
}	t_ray;

typedef struct s_intersection
{
	t_obj *obj;
	double	t;
}	t_intersection;

typedef struct s_xs
{
	t_intersection	*arr;
	size_t			size;
	size_t			curr;
	size_t			i;
	size_t			to_add;
}	t_xs;

typedef struct s_comps
{
	t_obj *obj;
	double	t;
	t_vct	point;
	t_vct	eye;
	t_vct	light;
	t_vct	normal;
	t_clr	color;
	t_vct	reflect;
	t_vct	over_point;
	t_vct	under_point;
	int		inside;
	double	n1;
	double	n2;
	double	schlick;
}	t_comps;

typedef struct s_worker
{
	t_mrt	*mrt;
	t_scene *scene;
	int		index;
	int		block_count;
	int		block_size;
	int		done;
	t_xs	xs;
}	t_worker;

#endif
