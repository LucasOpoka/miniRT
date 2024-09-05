/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:07:45 by atorma            #+#    #+#             */
/*   Updated: 2024/09/05 21:03:46 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

char	***array_matrix(char *data);
void	array_matrix_free(char ***arr);
char	*file_load(char *file);
int		identifier(void);
int		identifiers_validate(char ***elements);
int		cam_add(t_scene *scene, char **elem);
int		light_add(t_scene *scene, char **elem, int id);
int		obj_add(t_scene *scene, char **elem, int id);

int	parser_error(char *err_str)
{
	printf("Error\n%s\n", err_str);
	return (0);
}

int	parse_object(t_scene *scene, char **line)
{
	int		ret;
	int		id;

	ret = 0;
	id = identifier_type(line[0]);
	if (id == ID_CAMERA)
		ret = cam_add(scene, line);
	else if (id == ID_AMBIENT || id == ID_LIGHT || id == ID_LIGHT_POINT)
		ret = light_add(scene, line, id);
	else if (id >= ID_SPHERE)
		ret = obj_add(scene, line, id);
	return (ret);
}

int	parse_scene(t_scene *scene, char ***matrix)
{
	size_t	i;

	i = 0;
	if (!scene_init(scene))
		return (parser_error("failed to initialize scene"));
	if (!identifiers_validate(matrix))
		return (0);
	while (matrix[i])
	{
		if (!parse_object(scene, matrix[i]))
			return (parser_error("malfored object information detected"));
		i++;
	}
	return (1);
}

int	parse_file(char *file, t_scene *scene)
{
	char	***matrix;
	char	*data;
	int		ret;

	ret = 0;
	ft_bzero(scene, sizeof(t_scene));
	data = file_load(file);
	if (!data)
		return (0);
	matrix = array_matrix(data);
	if (!matrix)
	{
		free(data);
		return (parser_error("ft_split failed"));
	}
	ret = parse_scene(scene, matrix);
	array_matrix_free(matrix);
	free(data);
	if (!ret)
		scene_free(scene);
	return (ret);
}
