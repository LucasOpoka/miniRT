
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

int	validate_identifiers(char ***elements)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	while (elements[i])
	{
		if (identifier_type(elements[i][0]) == ID_UNKNOWN)
		{
			printf("Invalid identifier found!\n");
			return (0);
		}
		j = 0;
		while (j < i)
		{
			len = ft_strlen(elements[i][0]);
			if (len != 1 || (*elements[i][0] < 'A' && *elements[i][0] > 'Z'))
				break ;
			if (ft_strcmp(elements[j][0], elements[i][0]) == 0)
			{
				printf("duplicate found: %s\n", elements[j][0]);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
