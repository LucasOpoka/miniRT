/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:07:30 by atorma            #+#    #+#             */
/*   Updated: 2024/09/05 20:39:15 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../includes/parser.h"
#include "../../libft/libft.h"

double	ft_atof(const char *s);
int		validate_color(char *s);

int	fill_vector(t_vct *vector, char *s)
{
	size_t	i;
	double	val;
	char	*colon;

	i = 0;
	val = 0.0;
	while (i < 3 && *s)
	{
		colon = ft_strchr(s, ',');
		val = ft_atof(s);
		if (i == 0)
			vector->x = val;
		if (i == 1)
			vector->y = val;
		if (i == 2)
			vector->z = val;
		if (colon)
			s = colon + 1;
		i++;
	}
	return (1);
}

int	fill_color(t_clr *vector, char *s)
{
	size_t	i;
	double	val;
	char	*colon;

	i = 0;
	val = 0.0;
	if (!validate_color(s))
		return (0);
	while (i < 3 && *s)
	{
		colon = ft_strchr(s, ',');
		val = ft_atof(s);
		if (i == 0)
			vector->r = val / 255;
		if (i == 1)
			vector->g = val / 255;
		if (i == 2)
			vector->b = val / 255;
		if (colon)
			s = colon + 1;
		i++;
	}
	return (1);
}
