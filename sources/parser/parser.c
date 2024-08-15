
#include "../../libft/libft.h"
#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

size_t	array_size(char **arr);
void	array_free(char **arr);
char	*file_load(char *file);

int	validate_identifier(char *id)
{
	size_t	len;

	len = ft_strlen(id);
	if (len != 1 && len != 2)
		return (0);
	while (*id)
	{
		if (!ft_isalpha(*id))
			return (0);
		id++;
	}
	return (1);
}

int	validate_element(int i, char *e)
{
	if (i == 0 && !validate_identifier(e))
		return (0);
	return (1);
}

int	parse_line(char *line)
{
	char	**elements;
	size_t	i;

	i = 0;
	elements = ft_split(line, ' ');
	if (array_size(elements) <= 2 || array_size(elements) >= 7)
	{
		array_free(elements);
		return (0);
	}
	while (elements[i])
	{
		if (!validate_element(i, elements[i]))
		{
			array_free(elements);
			return (0);
		}
		printf("%s ", elements[i]);
		i++;
	}
	printf("\n");
	array_free(elements);
	return (1);
}

int	parse_data(char *data)
{
	char	**lines;
	size_t	i;

	i = 0;
	lines = ft_split(data, '\n');
	if (array_size(lines) < 6)
	{
		array_free(lines);
		return (0);
	}
	while (lines[i])
	{
		if (!parse_line(lines[i]))
		{
			array_free(lines);
			return (0);
		}
		i++;
	}
	printf("line_count: %zu\n", i);
	array_free(lines);
	return (1);
}

int	parse_file(char *file)
{
	char	*data;
	int		ret;

	ret = 0;
	data = file_load(file);
	if (!data)
		return (0);
	printf("scene %s raw data:\n %s\n-------------\n", file, data);
	ret = parse_data(data);
	free(data);
	return (ret);
}
