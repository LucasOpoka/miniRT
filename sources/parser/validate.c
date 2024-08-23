#include "../../libft/libft.h"
#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

int	validate_ratio(char	*s, double min, double max)
{
	size_t	len;
	double	ratio;

	len = ft_strlen(s);
	if (len != 3)
		return (0);
	if (!ft_isdigit(s[0]) || s[1] != '.' || !ft_isdigit(s[2]))
		return (0);
	ratio = ft_atof(s);
	if (ratio < min || ratio > max)
		return (0);
	return (1);
}

int	validate_vector(char *s)
{
	char	*comma;
	int		i;

	if (str_charcount(s, ',') != 2)
		return (0);
	i = 3;
	while (i-- > 0)
	{
		if (!str_isfloat(s))
			return (0);
		comma = ft_strchr(s, ',');
		if (!comma)
			break ;
		s = comma + 1;
	}

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
