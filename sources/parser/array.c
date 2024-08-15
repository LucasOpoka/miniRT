
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
