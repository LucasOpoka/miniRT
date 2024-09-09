/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:07:20 by atorma            #+#    #+#             */
/*   Updated: 2024/09/09 20:08:30 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../libft/libft.h"
#include <fcntl.h>

static int	file_validate_name(char *str, int type)
{
	const char	*extension = ".rt";
	char		*dot;

	if (type == e_file_ppm)
		extension = ".ppm";
	dot = ft_strrchr(str, '.');
	if (!dot)
		return (0);
	if (dot == str || ft_strcmp(dot, extension) != 0)
		return (0);
	return (1);
}

static int	valid_chars(char *s, int type)
{
	const char	*chars = "0123456789ACLplscytr -,.\n";

	if (type == e_file_ppm)
		return (0);
	while (*s)
	{
		if (type == e_file_scene && !ft_strchr(chars, *s))
			return (0);
		s++;
	}
	return (1);
}

static char	*file_read_data(int fd, size_t *out_size, int type)
{
	char	*data;
	size_t	size;

	data = read_file(fd, 2048, &size);
	if (!data || !size)
	{
		parser_error("unexpected error encounter while reading file");
		free(data);
		return (NULL);
	}
	*out_size = size;
	if (type == e_file_ppm)
		return (data);
	if (size != ft_strlen(data) || !valid_chars(data, type))
	{
		parser_error("invalid characters on the file");
		free(data);
		return (NULL);
	}
	return (data);
}

char	*file_load(char *file, size_t *out_size, int type)
{
	int		fd;
	char	*data;

	*out_size = 0;
	if (!file_validate_name(file, type))
	{
		parser_error("invalid filename");
		return (NULL);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		parser_error("could not open file");
		return (NULL);
	}
	data = file_read_data(fd, out_size, type);
	close(fd);
	return (data);
}
