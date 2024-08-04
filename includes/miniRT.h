/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:06:19 by lopoka            #+#    #+#             */
/*   Updated: 2024/08/04 16:27:15 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINIRT_H
# define MINIRT_H
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include "../sources/MLX42/include/MLX42/MLX42.h"
# define CANV_WDTH	1200
# define CANV_HGHT	1200
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

typedef struct s_sphere
{
	t_vct	position;
	float	radius;
	int		color;
}	t_sphere;

void		ft_show_img(t_mrt *mrt);

void		ft_loop_hook(void *vd);
void		ft_close_hook(void *vd);
void		ft_keyboard_hooks(mlx_key_data_t k_data, void *vd);

void		ft_init_stc(t_mrt *mrt, int ac, char **av);

void		ft_close(t_mrt *mrt, int code);

#endif
