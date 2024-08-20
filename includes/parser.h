
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

int		identifier_type(char *id);
int		parse_file(char *file, t_scene *scene);

#endif
