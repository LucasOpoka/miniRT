/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:32:21 by atorma            #+#    #+#             */
/*   Updated: 2024/06/19 14:32:23 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

static char	*re_alloc(void *ptr, int len, int new_len)
{
	char	*new;

	new = malloc(new_len);
	if (!new)
	{
		free(ptr);
		return (NULL);
	}
	ft_memcpy(new, ptr, len);
	free(ptr);
	return (new);
}

static char	*read_buffered(int fd, int buf_size,
		size_t *out_size, int *error)
{
	char	temp_buf[1024];
	ssize_t	size_read;
	size_t	total_read;
	char	*buf;

	buf = malloc(buf_size + 1);
	if (!buf)
		return (NULL);
	total_read = 0;
	while (1)
	{
		size_read = read(fd, temp_buf, sizeof(temp_buf));
		*error = size_read;
		if (size_read <= 0)
			break ;
		buf_size += sizeof(temp_buf);
		buf = re_alloc(buf, total_read, buf_size + 1);
		if (!buf)
			return (NULL);
		ft_memcpy(buf + total_read, temp_buf, size_read);
		total_read += size_read;
	}
	buf[total_read] = 0;
	*out_size = total_read;
	return (buf);
}

char	*read_file(int fd, int buf_size, size_t *out_size)
{
	int		error;
	char	*data;

	*out_size = 0;
	error = -1;
	data = read_buffered(fd, buf_size, out_size, &error);
	if (error == -1)
	{
		free(data);
		return (NULL);
	}
	return (data);
}
