/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:43:35 by atorma            #+#    #+#             */
/*   Updated: 2024/09/21 19:34:34 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PARSER_H
# define PARSER_H

enum
{
	e_id_ambient,
	e_id_camera,
	e_id_light,
	e_id_light_point,
	e_id_sphere,
	e_id_plane,
	e_id_cylinder,
	e_id_cone,
	e_id_triangle,
	e_id_unknown
};

enum
{
	e_file_scene,
	e_file_ppm
};

char	*file_load(char *file, size_t *out_size, int type);
int		parser_error(char *err_str);
int		str_isdigit(char *s);
int		str_isdouble(char *s);
size_t	str_charcount(char *s, int c);
size_t	len_till(char *s, int c);
size_t	array_size(char **arr);
void	array_free(char **arr);
double	ft_atof(const char *s);
int		fill_vector(t_vct *vector, char	*s);
int		fill_color(t_clr *vector, char	*s);
int		identifier_type(char *id);
int		parse_file(char *file, t_scene *scene);
int		validate_ratio(char	*s, double min, double max);
int		validate_vector(char *s);
int		light_add_ambient(t_ambient *ambient, char **elem);
int		light_add_point(t_light *light, char **elem);
int		sphere_add(t_obj *obj, char **elem);
int		plane_add(t_obj *obj, char **elem);
int		cylinder_add(t_obj *obj, char **elem);

#endif
