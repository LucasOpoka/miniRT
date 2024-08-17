
#include "../../libft/libft.h"
#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

size_t	array_size(char **arr);
void	array_free(char **arr);
char	***array_matrix(char *data);
void	print_matrix(char ***m);
void	array_matrix_free(char ***arr);
char	*file_load(char *file);
int		validate_identifiers(char ***elements);

int	parse_object(char **object, int id)
{
	size_t	i;

	i = 0;
	printf("OBJ:\t%d", id);
	while (object[i])
	{
		printf("\t%s", object[i]);
		i++;
	}
	printf("\n");
	return (1);
}

int	parse_shape(char **shape, int id)
{
	size_t	i;

	i = 0;
	printf("SHAPE: \t%d", id);
	while (shape[i])
	{
		//void arr
		printf("\t%s", shape[i]);
		/*
		 if (!valid_color() return 0
		 */
		i++;
	}
	printf("\n");
	return (1);
}

int	parse_line(char **line)
{
	int		ret;
	int		id;

	id = identifier_type(line[0]);

	ret = 1;
	if (id >= ID_SPHERE)
		ret = parse_shape(line, id);
	else if (id >= ID_AMBIENT)
		ret = parse_object(line, id);
	return (ret);
}

int	parse_scene(char ***matrix)
{
	size_t	i;

	i = 0;
	if (!matrix)
		return (0);
	if (!validate_identifiers(matrix))
	{
		printf("Error: validate_identifiers\n");
		return (0);
	}
	while (matrix[i])
	{
		if (!parse_line(matrix[i]))
			return (0);
		i++;
	}
	printf("line_count: %zu\n", i);
	return (1);
}


int	parse_file(char *file)
{
	char	***matrix;
	char	*data;
	int		ret;

	ret = 0;
	data = file_load(file);
	if (!data)
		return (0);
	printf("scene %s raw data:\n %s\n-------------\n", file, data);

	matrix = array_matrix(data);
	ret = parse_scene(matrix);
	array_matrix_free(matrix);

	free(data);
	return (ret);
}
