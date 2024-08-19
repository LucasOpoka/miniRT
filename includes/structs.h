/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:16:04 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/18 13:38:14 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef STRUCTS_H
# define STRUCTS_H

typedef float	t_mtrx2[2][2];
typedef float	t_mtrx3[3][3];
typedef float	t_mtrx4[4][4];

typedef struct s_mrt
{
	mlx_t			*mlx;
	mlx_image_t		*img;
}	t_mrt;

typedef struct s_vct
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vct;

typedef struct s_clr
{
	float	r;
	float	g;
	float	b;
}	t_clr;

typedef struct s_shape
{
	int		type;
	t_vct	position;
	float	radius;
	t_clr	color;
	int		specular;
	float	reflective;
	t_vct	orientation;
}	t_shape;

typedef struct s_light
{
	int		type;
	float	intensity;
	t_vct	position;
	t_vct	direction;
}	t_light;

typedef enum e_light_type
{
	t_ambient,
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

typedef struct t_camera
{
	t_vct	position;
	t_vct	direction;
	float	fov;
	float	pixel_size;
	float	half_wdth;
	float	half_hght;
	t_mtrx4	world_to_camera;
	t_mtrx4	camera_to_world;
}	t_camera;

typedef	struct t_scene
{
	t_camera	camera;
	t_void_arr	lights;
	t_void_arr	shapes;
}	t_scene;

#endif
