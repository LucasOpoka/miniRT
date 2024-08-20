
#include "../../libft/libft.h"
#include "../../includes/miniRT.h"
#include "../../includes/parser.h"

double	ft_atof(const char *s);
int		validate_color(char *s);

int	fill_vector(t_vct *vector, char	*s)
{
	size_t	i = 0;
	double	val = 0.0;
	char	*colon;

	while(i < 3 && *s)
	{
		colon = ft_strchr(s, ',');
		val = ft_atof(s);
		if (i == 0)
			vector->x = val;
		if (i == 1)
			vector->y = val;
		if (i == 2)
			vector->z = val;
		if (colon)
			s = colon + 1;
		i++;
	}
	return (1);
}

int	fill_color(t_clr *vector, char	*s)
{
	size_t	i = 0;
	double	val = 0.0;
	char	*colon;

	if (!validate_color(s))
	{
		printf("INVALID COLOR\n");
		return (0);
	}
	while(i < 3 && *s)
	{
		colon = ft_strchr(s, ',');
		val = ft_atof(s);
		if (i == 0)
			vector->r = val;
		if (i == 1)
			vector->g = val;
		if (i == 2)
			vector->b = val;
		if (colon)
			s = colon + 1;
		i++;
	}
	return (1);
}
