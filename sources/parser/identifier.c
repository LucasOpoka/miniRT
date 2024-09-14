/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:07:36 by atorma            #+#    #+#             */
/*   Updated: 2024/09/14 18:22:18 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

int	identifier_type(char *id);
int	valid_obj_count(char **line, int id);

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
		if (!valid_obj_count(elements[i],
				identifier_type(elements[i][0])))
		{
			parser_error("invalid element count on an object");
			return (0);
		}
		i++;
	}
	return (1);
}
