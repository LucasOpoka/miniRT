
#ifndef PARSER_H
# define PARSER_H

enum
{
	ID_AMBIENT,
	ID_CAMERA,
	ID_LIGHT,
	ID_SPHERE,
	ID_PLANE,
	ID_CYLINDER,
	ID_UNKNOWN
};

void	print_vector(t_vct v);
void	print_color(t_clr v);
int		str_isdigit(char *s);
int		str_isfloat(char *s);
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
int		validate_coords(char *s);

#endif
