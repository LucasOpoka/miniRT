/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:21:45 by atorma            #+#    #+#             */
/*   Updated: 2024/09/14 18:22:05 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

int	identifier_type(char *id)
{
	const char	*identifiers[] = {"A", "C", "L", "l", "sp", "pl", "cy", 0};
	size_t		i;

	i = 0;
	while (identifiers[i])
	{
		if (ft_strcmp(id, identifiers[i]) == 0)
			return (i);
		i++;
	}
	return (i);
}

int	valid_obj_count(char **line, int id)
{
	const size_t	expected[] = {3, 4, 4, 4, 4, 4, 6, 0};
	size_t			count;

	count = array_size(line);
	if (expected[id] != count)
		return (0);
	return (1);
}
