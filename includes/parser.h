/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:43:35 by atorma            #+#    #+#             */
/*   Updated: 2024/09/05 20:56:51 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
# define PARSER_H

#define BONUS

enum
{
	ID_AMBIENT,
	ID_CAMERA,
	ID_LIGHT,
	ID_LIGHT_POINT,
	ID_SPHERE,
	ID_PLANE,
	ID_CYLINDER,
	ID_UNKNOWN
};

enum
{
	e_file_scene,
	e_file_ppm
};

char	*file_load(char *file, int type);
int	parser_error(char *err_str);
int	str_isdigit(char *s);
int	str_isdouble(char *s);
size_t	str_charcount(char *s, int c);
size_t	len_till(char *s, int c);
size_t	array_size(char **arr);
void	array_free(char **arr);
double	ft_atof(const char *s);
int	fill_vector(t_vct *vector, char	*s);
int	fill_color(t_clr *vector, char	*s);
int	identifier_type(char *id);
int	parse_file(char *file, t_scene *scene);
int	validate_ratio(char	*s, double min, double max);
int	validate_vector(char *s);
int	light_add_ambient(t_ambient *ambient, char **elem);
int	light_add_point(t_light *light, char **elem);

#endif
