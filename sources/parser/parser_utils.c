#include "../../libft/libft.h"
#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

int	str_isdigit(char *s)
{
	if (*s == '\0')
		return (0);
	while (*s)
	{
		if (ft_isdigit(!s))
			return (0);
		s++;
	}
	return (1);
}

size_t	len_till(char *s, int c)
{
	char	*character;

	character = ft_strchr(s, c);
	if (character)
		return (character - s);
	return (ft_strlen(s));
}
