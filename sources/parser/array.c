
#include "../../libft/libft.h"
#include "../../includes/miniRT.h"

size_t	array_size(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return (i);
	while (arr[i])
		i++;
	return (i);
}

void	array_free(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
void	array_matrix_free(char ***arr)
{
	size_t	i;

	i = 0;
	while (arr && arr[i])
		array_free(arr[i++]);
	free(arr);
}

char	***array_matrix(char *data)
{
	char	***ret;
	char	**lines;
	size_t	i;

	i = 0;
	lines = ft_split(data, '\n');
	if (array_size(lines) < 6)
	{
		free_array(lines);
		return (NULL);
	}
	ret = ft_calloc(1, sizeof(char **) * (array_size(lines) + 1));
	while(ret && lines[i])
	{
		ret[i] = ft_split(lines[i], ' ');
		if (!ret[i] || array_size(ret[i]) <= 2 || array_size(ret[i]) >= 7)
		{
			array_matrix_free(ret);
			ret = NULL;
			break ;
		}
		i++;
	}
	array_free(lines);
	return (ret);
}

void	print_matrix(char ***m)
{
	int i = 0;
	while (m[i])
	{
		int j = 0;
		while (m[i][j])
		{
			printf("%s ", m[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

