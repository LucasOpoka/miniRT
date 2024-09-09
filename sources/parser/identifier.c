/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:07:36 by atorma            #+#    #+#             */
/*   Updated: 2024/09/09 22:51:56 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../includes/parser.h"
#include "../../libft/libft.h"

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

static int	validate_object_count(char **line, int id)
{
	const size_t	expected[] = {3, 4, 4, 4, 4, 4, 6, 0};
	size_t			count;
	size_t			expected_value;

	count = array_size(line);
	expected_value = expected[id];
#ifdef BONUS
	// Light point direction vct
	if (id == 2 || id == 3)
		expected_value += 1;
	// Obj bonus fields
	if (id >= 4)
		expected_value += 7;
#endif
	if (expected_value != count)
		return (0);
	return (1);
}

static int	identifiers_check(char ***elements)
{
	size_t	i;
	int		found[16];
	int		id;

	i = 0;
	ft_bzero(found, 16 * sizeof(int));
	while (elements[i])
	{
		id = identifier_type(elements[i][0]);
		if (id == e_id_unknown)
			return (0);
		found[id] += 1;
		i++;
	}
	if (found[e_id_camera] != 1 || found[e_id_ambient] != 1 || found[e_id_light] != 1)
		return (0);
	return (1);
}

int	identifiers_validate(char ***elements)
{
	size_t	i;

	i = 0;
	if (!identifiers_check(elements))
	{
		parser_error("invalid or duplicate identifiers");
		return (0);
	}
	while (elements[i])
	{
		if (!validate_object_count(elements[i],
				identifier_type(elements[i][0])))
		{
			parser_error("invalid element count on an object");
			return (0);
		}
		i++;
	}
	return (1);
}
