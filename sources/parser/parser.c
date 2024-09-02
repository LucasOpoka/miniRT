/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:07:45 by atorma            #+#    #+#             */
/*   Updated: 2024/08/24 18:07:47 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

size_t	array_size(char **arr);
void	array_free(char **arr);
char	***array_matrix(char *data);
void	array_matrix_free(char ***arr);
void	print_matrix(char ***m);
char	*file_load(char *file);
int		identifiers_validate(char ***elements);
t_vct	ft_create_vct(double x, double y, double z);
t_clr	ft_create_clr(double r, double g, double b);
int		cam_add(t_scene *scene, char **elem);
int		light_add(t_scene *scene, char **elem, int id);
int		obj_add(t_scene *scene, char **elem, int id);

void	print_vector(t_vct v)
{
	printf("VECTOR: x: %f, y: %f, z: %f\n", v.x, v.y, v.z);
}

void	print_color(t_clr v)
{
	printf("COLOR: r: %f, g: %f, b: %f\n", v.r, v.g, v.b);
}

void	parser_error(char *err_str)
{
	printf("Error\n%s\n", err_str);
}

int	parse_object(t_scene *scene, char **line)
{
	int		ret;
	int		id;

	ret = 0;
	id = identifier_type(line[0]);
	if (id == ID_CAMERA)
		ret = cam_add(scene, line);
	else if (id == ID_AMBIENT || id == ID_LIGHT)
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
	{
		parser_error("failed to initialize scene");
		return (0);
	}
	if (!identifiers_validate(matrix))
		return (0);
	while (matrix[i])
	{
		if (!parse_object(scene, matrix[i]))
		{
			parser_error("malfored object information detected");
			return (0);
		}
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
		parser_error("ft_split failed");
		free(data);
		return (0);
	}
	ret = parse_scene(scene, matrix);
	array_matrix_free(matrix);
	free(data);
	if (!ret)
		scene_free(scene);
	return (ret);
}
