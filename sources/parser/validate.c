/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:07:57 by atorma            #+#    #+#             */
/*   Updated: 2024/09/09 23:55:55 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../includes/parser.h"
#include "../../libft/libft.h"

int	validate_orientation(t_vct v)
{
	if (v.x < -1.0 || v.y < -1.0 || v.z < -1.0)
		return (0);
	if (v.x > 1.0 || v.y > 1.0 || v.z > 1.0)
		return (0);
	return (1);
}

int	validate_ratio(char *s, double min, double max)
{
	const char		*dot = ft_strchr(s, '.');
	const size_t	len = ft_strlen(s);
	size_t			i;
	double			ratio;

	i = 0;
	if (dot)
	{
		if (str_charcount(s, '.') != 1)
			return (0);
		if (len < 3 || dot != (s + 1))
			return (0);
	}
	while (i < len)
	{
		if (s[i] != '.' && !ft_isdigit(s[i]))
			return (0);
		i++;
	}
	ratio = ft_atof(s);
	if (!isfinite(ratio) || ratio < min || ratio > max)
		return (0);
	return (1);
}

int	validate_vector(char *s)
{
	char	*comma;
	int		i;

	if (str_charcount(s, ',') != 2)
		return (0);
	i = 3;
	while (i-- > 0)
	{
		if (!str_isdouble(s))
			return (0);
		comma = ft_strchr(s, ',');
		if (!comma)
			break ;
		s = comma + 1;
	}
	return (1);
}

int	validate_color(char *s)
{
	char	*comma;
	size_t	len;

	if (str_charcount(s, ',') != 2)
		return (0);
	comma = ft_strchr(s, ',');
	while (comma)
	{
		len = len_till(s, ',');
		if (len < 1 || len > 3)
			return (0);
		if (ft_atof(s) < 0 || ft_atof(s) > 255)
			return (0);
		while (len--)
		{
			if (!ft_isdigit(s[len]))
				return (0);
		}
		comma = ft_strchr(s, ',');
		if (!comma)
			break ;
		s = comma + 1;
	}
	return (1);
}
