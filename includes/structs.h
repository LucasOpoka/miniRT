/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:16:04 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/17 21:25:58 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef STRUCTS_H
# define STRUCTS_H

# include "worker.h"

typedef double			t_mtrx2[2][2];
typedef double			t_mtrx3[3][3];
typedef double			t_mtrx4[4][4];

typedef struct s_worker	t_worker;
typedef struct s_ptrn	t_ptrn;
// typedef	struct	s_ppm t_ppm;

typedef struct s_mrt
{
	mlx_t				*mlx;
	mlx_image_t			*img;
	struct s_worker		*workers;
	pthread_t			threads[MAX_THREADS + 1];
	size_t				thread_count;
	int					threads_finished;
	pthread_mutex_t		lock;
	pthread_cond_t		notify;
	pthread_cond_t		complete;
	int					do_render;
	int					exit;
}						t_mrt;

typedef struct s_bounds
{
	double				min[3];
	double				max[3];
}						t_bounds;

typedef struct s_aabb_time
{
	double				t1;
	double				t2;
	double				t3;
	double				t4;
	double				t5;
	double				t6;
}						t_aabb_time;

typedef struct s_node
{
	t_bounds			bounds;
	uint32_t			left;
	uint32_t			first_index;
	uint32_t			count;
}						t_node;

typedef struct s_split
{
	double				cost;
	double				pos;
	int				axis;
}						t_split;

typedef struct s_stack
{
	t_node				*stack[64];
	uint32_t			ptr;
}						t_stack;

typedef struct s_bvh
{
	t_node				*root;
	uint32_t			*i;
	uint32_t			nodes_used;
}						t_bvh;

typedef struct s_vct
{
	double				x;
	double				y;
	double				z;
	double				w;
}						t_vct;

typedef struct s_clr
{
	double				r;
	double				g;
	double				b;
}						t_clr;

typedef struct s_ptrn
{
	t_clr				(*ptrn_func)(double *uv, double width, double height);
	double				wdth;
	double				hght;
} t_ptrn;

typedef struct s_ppm
{
	int					ptr;
	char				*data;
	size_t				data_size;
	char				*line;
	uint32_t			max_color;
	uint32_t			width;
	uint32_t			height;
	t_clr				**colors;
}						t_ppm;

typedef struct s_obj
{
	float				centroid[3];
	int					type;
	t_vct				pos;
	t_clr				color;
	double				specular;
	double				diffuse;
	int					shininess;
	double				reflective;
	double				refractive;
	double				transparency;
	t_vct				orientation;
	t_vct				scale;
	t_mtrx4				obj_to_world;
	t_mtrx4				world_to_obj;
	t_mtrx4				normal_to_world;
	t_vct				normal;
	t_vct				e1;
	t_vct				e2;
	t_vct				p1;
	t_vct				p2;
	t_vct				p3;
	t_ppm				txtr;
	t_ppm				bump;
	double				bump_modifier;
	t_ptrn				ptrn;
}						t_obj;

typedef struct s_light
{
	int					type;
	double				intensity;
	t_vct				pos;
	t_vct				dir;
	t_clr				color;
}						t_light;

typedef enum e_light_type
{
	t_point,
	t_diral
}						t_light_type;

typedef enum e_obj_type
{
	t_sphere,
	t_plane,
	t_cylinder,
	t_triangle,
	t_cone
}						t_obj_type;

typedef struct s_void_arr
{
	void				**arr;
	size_t				size;
	size_t				i;
	size_t				to_add;
}						t_void_arr;

typedef struct s_cam
{
	t_vct				pos;
	t_vct				dir;
	double				fov;
	double				pixel_size;
	double				half_wdth;
	double				half_hght;
	t_mtrx4				world_to_cam;
	t_mtrx4				cam_to_world;
}						t_cam;

typedef struct t_ambient
{
	double				intensity;
	t_clr				color;
}						t_ambient;

typedef struct s_scene
{
	t_cam				cam;
	t_ambient			ambient;
	t_void_arr			lights;
	t_void_arr			objs;
	t_bvh				bvh;
}						t_scene;

typedef struct s_ray
{
	t_vct				O;
	t_vct				D;
	t_vct				rd;
}						t_ray;

typedef struct s_intrsc
{
	t_obj				*obj;
	double				t;
}						t_intrsc;

typedef struct s_xs
{
	t_intrsc			*arr;
	size_t				size;
	size_t				i;
	size_t				to_add;
}						t_xs;

typedef struct s_cl_xs
{
	double				a;
	double				b;
	double				c;
	double				disc;
	double				t[2];
	double				tmp;
	double				y[2];
}						t_cl_xs;

typedef struct s_tri_xs
{
	t_vct				dir_cros_e2;
	double				det;
	double				f;
	t_vct				p1_to_origin;
	double				u;
	t_vct				origin_cross_e1;
	double				v;
	double				t;
}						t_tri_xs;

typedef struct s_comps
{
	t_intrsc			*hit;
	t_obj				*obj;
	double				t;
	t_vct				point;
	t_vct				eye;
	t_vct				light;
	t_vct				normal;
	t_clr				color;
	t_vct				reflect;
	t_vct				over_point;
	t_vct				under_point;
	int					inside;
	double				n1;
	double				n2;
	double				schlick;
}						t_comps;

typedef struct s_phong
{
	t_clr				result;
	t_clr				effective;
	t_clr				diffuse;
	t_clr				specular;
	t_vct				light_vct;
	double				lght_dot_norm;
}						t_phong;

typedef struct s_clr_recur
{
	t_ray				ray;
	t_scene				*scene;
	t_xs				*xs;
	t_comps				comps;
	t_light				*light;
	int					recur_lmt;
}						t_clr_recur;

typedef struct s_refraction
{
	t_clr				res;
	double				n_ratio;
	double				transparency;
	double				cos_i;
	double				sin2_t;
	double				cos_t;
	t_vct				v1;
	t_vct				v2;
}						t_refraction;

typedef struct s_worker
{
	t_mrt				*mrt;
	t_scene				*scene;
	int					index;
	int					block_count;
	int					block_size;
	int					done;
	t_xs				xs;
}						t_worker;

typedef struct s_txtr_bump
{
	uint32_t			x;
	uint32_t			y;
	double				theta;
	double				radius;
	double				phi;
	t_vct				tan;
	t_vct				bitan;
	double				h1;
	double				h_uv;
	double				h2;
	t_vct				obj_norm;
	t_vct				q_u;
	t_vct				q_v;
}						t_txtr_bump;
#endif
