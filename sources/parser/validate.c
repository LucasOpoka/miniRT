
#include "../../libft/libft.h"
#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

/*
static int	validate_id(char *id)
{
	size_t	len;

	len = ft_strlen(id);
	if (len != 1 && len != 2)
		return (0);
	while (*id)
	{
		if (!ft_isalpha(*id))
			return (0);
		id++;
	}
	return (1);
}
*/

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

int	validate_identifiers(char ***elements)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	while (elements[i])
	{
		if (identifier_type(elements[i][0]) == ID_UNKNOWN)
			return (0);
		len = ft_strlen(elements[i][0]);
		j = 0;
		while (j < i)
		{
			if (len != 1 && *elements[i][0] < 'A' && *elements[i][0] > 'Z')
				break ;
			if (ft_strcmp(elements[j][0], elements[i][0]) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
