/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopoka <lopoka@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:06:19 by lopoka            #+#    #+#             */
/*   Updated: 2024/09/01 15:19:41 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINIRT_H
# define MINIRT_H
# include <stdlib.h>
# include <math.h>
# include <float.h>
# include <stdio.h>
# include "../sources/MLX42/include/MLX42/MLX42.h"
# include "structs.h"
# include "parser.h"
# include "mtrx.h"
# include "vct.h"
# include "camera.h"
# include "shapes_transforms.h"
# include "intersections.h"
# include "prep_comps.h"
# include "shapes_normals.h"
# include "get_color.h"
# include "lighting.h"
# include "clr_math.h"
# include "../libft/libft.h"

# define EPSILON	0.0001f
# define MAYA_STYLE	0
# define CANV_WDTH	640
# define CANV_HGHT	640
# define FOV		53
//# define FOV		25.7831
# define VIEW_WDTH	1
# define VIEW_HGHT	1
# define DISTANCE	1


void		ft_show_img(t_mrt *mrt, t_scene *scene);
t_clr		ft_create_clr(double r, double g, double b);

void		ft_loop_hook(void *vd);
void		ft_close_hook(void *vd);
void		ft_keyboard_hooks(mlx_key_data_t k_data, void *vd);

void		ft_init_stc(t_mrt *mrt);

void		ft_close(t_mrt *mrt);

// Void array
void		ft_init_void_arr(t_void_arr *void_arr);
void		ft_void_arr_realloc(t_void_arr *void_arr);
void		ft_void_arr_add(t_void_arr *void_arr, void *pointer);
void		ft_free_void_arr(t_void_arr *void_arr);

// t_xs
void		ft_init_xs(t_xs *xs);
void		ft_free_xs(t_xs *xs);
void		ft_add_intersection(t_xs *xs, t_shape *shape, double t);

int				scene_init(t_scene *scene);
void			scene_free(t_scene *scene);
// REMOVE IN THE FUTURE - test functions
t_scene			get_test_scene(void);

#endif
