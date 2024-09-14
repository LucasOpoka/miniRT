/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:15:26 by atorma            #+#    #+#             */
/*   Updated: 2024/09/14 18:24:23 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

int	identifier_type(char *id)
{
	const char	*ids[] = {"A", "C", "L", "l", "sp", "pl", "cy", "co", "tr", 0};
	size_t		i;

	i = 0;
	while (ids[i])
	{
		if (ft_strcmp(id, ids[i]) == 0)
			return (i);
		i++;
	}
	return (i);
}

int	valid_obj_count(char **line, int id)
{
	const size_t	expected[] = {3, 4, 4, 4, 4, 4, 6, 6, 6, 0};
	const size_t	count = array_size(line);
	size_t		value;

	value = expected[id];
	// Light point direction vct
	if (id == 2 || id == 3)
		value += 1;
	// Obj bonus fields + texture & bmp
	if (id >= e_id_sphere)
		value += 10;
	if (value != count)
		return (0);
	return (1);
}
