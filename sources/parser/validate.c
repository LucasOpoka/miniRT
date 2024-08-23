
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


int	validate_ratio(char	*s, double min, double max)
{
	char	*comma;
	size_t	len_str;

	len_str = ft_strlen(s);
	comma = ft_strchr(s, ',');
	if (len_str != 7 || !comma)
		return (0);
	if (ft_atof(s) < min || ft_atof(comma + 1) > max)
		return (0);
	return (1);
}

int	validate_color(char *s)
{
	char	*comma;
	size_t	count;
	size_t	len;

	count = 0;
	while (*s)
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
		count++;
		s = comma + 1;
	}
	return (count == 2);
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

int	validate_identifiers(char ***elements)
{
	size_t	i;

	i = 0;
	while (elements[i])
	{
		if (identifier_type(elements[i][0]) == ID_UNKNOWN)
		{
			printf("Invalid identifier found!\n");
			return (0);
		}
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
