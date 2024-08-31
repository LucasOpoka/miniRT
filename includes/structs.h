/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:16:04 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/31 18:02:22 by lucas            ###   ########.fr       */
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
}	t_mrt;

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

typedef struct s_shape
{
	int		type;
	t_vct	position;
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
	t_mtrx4	shape_to_world;
	t_mtrx4	world_to_shape;
	t_mtrx4	normal_to_world;
}	t_shape;

typedef struct s_light
{
	int		type;
	double	intensity;
	t_vct	position;
	t_vct	direction;
	t_clr	color;
}	t_light;

typedef enum e_light_type
{
	t_point,
	t_directional
}	t_light_type;

typedef enum e_shape_type
{
	t_sphere,
	t_plane,
	t_cylinder
}	t_shape_type;

typedef struct s_void_arr
{
	void	**arr;
	size_t	size;
	size_t	curr;
	size_t	i;
	size_t	to_add;
}	t_void_arr;

typedef struct s_camera
{
	t_vct	position;
	t_vct	direction;
	double	fov;
	double	pixel_size;
	double	half_wdth;
	double	half_hght;
	t_mtrx4	world_to_camera;
	t_mtrx4	camera_to_world;
}	t_camera;

typedef	struct	t_ambient
{
	double	intensity;
	t_clr	color;
}	t_ambient;

typedef	struct s_scene
{
	t_camera	camera;
	t_ambient	ambient;
	t_void_arr	lights;
	t_void_arr	shapes;
}	t_scene;

typedef	struct s_ray
{
	t_vct	O;
	t_vct	D;
}	t_ray;

typedef struct s_intersection
{
	t_shape *shape;
	double	t;
}	t_intersection;

typedef struct s_comps
{
	t_shape *shape;
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

typedef struct t_worker
{
	t_mrt	*mrt;
	t_scene *scene;
	int		index;
	int		block_count;
	int		block_size;
	int		done;
	t_void_arr	intersections;
}	t_worker;

#endif
