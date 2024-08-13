/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:06:19 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/13 16:36:08 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINIRT_H
# define MINIRT_H
# include <stdlib.h>
# include <math.h>
# include <float.h>
# include <stdio.h>
# include "../sources/MLX42/include/MLX42/MLX42.h"
# define CANV_WDTH	1100
# define CANV_HGHT	1100
# define VIEW_WDTH	1
# define VIEW_HGHT	1
# define DISTANCE	1

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
}	t_vct;

typedef struct s_clr
{
	float	r;
	float	g;
	float	b;
}	t_clr;

typedef struct s_sphere
{
	t_vct	position;
	float	radius;
	t_clr	color;
	int		specular;
	float	reflective;
}	t_sphere;

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

void		ft_show_img(t_mrt *mrt);

void		ft_loop_hook(void *vd);
void		ft_close_hook(void *vd);
void		ft_keyboard_hooks(mlx_key_data_t k_data, void *vd);

void		ft_init_stc(t_mrt *mrt, int ac, char **av);

void		ft_close(t_mrt *mrt, int code);

#endif
