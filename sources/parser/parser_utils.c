/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:07:50 by atorma            #+#    #+#             */
/*   Updated: 2024/08/24 18:07:51 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

int	str_isdigit(char *s)
{
	if (*s == '\0')
		return (0);
	while (*s)
	{
		if (ft_isdigit(!s))
			return (0);
		s++;
	}
	return (1);
}

size_t	str_charcount(char *s, int c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s == c)
			count++;
		s++;
	}
	return (count);
}

int	str_isfloat(char *s)
{
	size_t	i;
	size_t	len;

	if (*s == '-')
		s++;
	i = 0;
	len = len_till(s, ',');
	if (len < 1 || len > 7 || (str_charcount(s, '.') > 1))
		return (0);
	while (i < len)
	{
		if (s[i] == '.')
		{
			if (i == 0 || s[i + 1] == '\0')
				return (0);
			i++;
		}
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

size_t	len_till(char *s, int c)
{
	char	*character;

	character = ft_strchr(s, c);
	if (character)
		return (character - s);
	return (ft_strlen(s));
}
