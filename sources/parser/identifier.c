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

static int	check_duplicates(char ***elements, int i)
{
	int		j;
	size_t	len;

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
		if (id == ID_CAMERA)
			found[0] += 1;
		if (id == ID_AMBIENT)
			found[1] += 1;
		i++;
	}
	if (!found[0] || !found[1])
		return (0);
	return (1);
}

int	identifiers_validate(char ***elements)
{
	size_t	i;

	i = 0;
	if (!identifiers_check(elements))
		return (0);
	while (elements[i])
	{
		if (!validate_object_count(elements[i], identifier_type(elements[i][0])))
		{
			printf("Invalid object count!\n");
			return (0);
		}
		if (!check_duplicates(elements, i))
		{
			printf("Duplicate entries found!\n");
			return (0);
		}
		i++;
	}
	return (1);
}
