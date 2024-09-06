/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:07:20 by atorma            #+#    #+#             */
/*   Updated: 2024/08/24 18:07:22 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../includes/miniRT.h"
#include <fcntl.h>

static int	file_validate_name(char	*str, int type)
{
	const char  *extension = ".rt";
	char	    *dot;

	if (type == e_file_ppm)
		extension = ".ppm";
	dot = ft_strrchr(str, '.');
	if (!dot)
		return (0);
	if (dot == str || ft_strcmp(dot, extension) != 0)
		return (0);
	return (1);
}

static	int	valid_chars(char *s, int type)
{
	const char	*chars = "0123456789ACLplscytr -,.\n";

	while (*s)
	{
		if (type == e_file_ppm && !ft_isascii(*s))
			return (0);
		if (type == e_file_scene && !ft_strchr(chars, *s))
			return (0);
		s++;
	}
	return (1);
}

static char	*file_read_data(int fd, int type)
{
	size_t	size;
	char	*data;

	size = 0;
	data = read_file(fd, 1024, &size);
	if (!data)
	{
		parser_error("unexpected error encounter while reading file");
		return (NULL);
	}
	if (!size)
	{
		parser_error("file is empty");
		free(data);
		return (NULL);
	}
	if (size != ft_strlen(data) || !valid_chars(data, type))
	{
		parser_error("invalid characters on the file");
		free(data);
		return (NULL);
	}
	return (data);
}

char	*file_load(char *file, int type)
{
	int		fd;
	char	*data;

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
	data = file_read_data(fd, type);
	close(fd);
	return (data);
}
