/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:19:27 by atorma            #+#    #+#             */
/*   Updated: 2024/08/17 11:14:32 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putstr_fd(char *s, int fd)
{
	unsigned int	len;
	size_t			bytes_written;

	bytes_written = 0;
	len = ft_strlen(s);
	if (len > 0)
		write(fd, s, len);
	return (bytes_written);
}
