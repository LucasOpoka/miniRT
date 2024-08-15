
#include "../../libft/libft.h"
#include "../../includes/miniRT.h"
#include <fcntl.h>

static int	file_validate_name(char	*str)
{
	char	*dot;

	dot = ft_strrchr(str, '.');
	if (!dot)
		return (0);
	if (ft_strcmp(dot, ".rt") != 0)
		return (0);
	return (1);
}

static	int	valid_chars(char *s)
{
	const char	*chars = "-,.\n ";

	while (*s)
	{
		if (!ft_isalnum(*s) && !ft_strchr(chars, *s))
			return (0);
		s++;
	}
	return (1);
}

static char	*file_read_data(int fd)
{
	size_t	size;
	char	*data;

	size = 0;
	data = read_file(fd, 1024, &size);
	if (!data)
		return (NULL);
	if (size != ft_strlen(data) || !valid_chars(data))
	{
		free(data);
		return (NULL);
	}
	return (data);
}

char	*file_load(char *file)
{
	int		fd;
	char	*data;

	if (!file_validate_name(file))
	{
		printf("Error: Invalid filename\n");
		return (NULL);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		return (NULL);
	}
	data = file_read_data(fd);
	close(fd);
	return (data);
}
