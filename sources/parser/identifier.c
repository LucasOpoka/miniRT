#include "../../libft/libft.h"
#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

int	identifier_type(char *id)
{
	const char	*identifiers[] = {"A", "C", "L", "sp", "pl", "cy", 0 };
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
	const size_t	expected[] = { 3, 4, 4, 4, 4, 6, 0};
	size_t	count;

	count = array_size(line);
	if (expected[id] != count)
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
		if (id == ID_UNKNOWN)
			return (0);
		found[id] += 1;
		i++;
	}
	if (found[ID_CAMERA] != 1 || found[ID_AMBIENT] != 1 || found[ID_LIGHT] != 1)
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
		if (!validate_object_count(elements[i], identifier_type(elements[i][0])))
		{
			parser_error("invalid element count on an object");
			return (0);
		}
		i++;
	}
	return (1);
}
