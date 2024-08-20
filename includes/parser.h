
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

size_t	array_size(char **arr);
void	array_free(char **arr);
double	ft_atof(const char *s);
void	fill_vector(t_vct *vector, char	*s);
void	fill_color(t_clr *vector, char	*s);
int		identifier_type(char *id);
int		parse_file(char *file, t_scene *scene);

#endif
