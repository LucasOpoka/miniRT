
#include "../../includes/miniRT.h"
#include "../../includes/ppm.h"

char *line_next(t_ppm *ppm)
{
	char  *newline = ft_strchr(ppm->line, '\n');

	if (!newline)
		return (NULL);
	if (*ppm->line == '#')
		return (newline + 1);
	ppm->ptr += 1;
	return (newline + 1);
}

void	line_print(t_ppm *ppm)
{
	
	char  *newline = ft_strchr(ppm->line, '\n');

	if (!newline)
		return ;
	write(1, ppm->line, (newline - ppm->line) + 1);
}

char  *line_next_pixel(char *s, int delim)
{
	const char *start = s;

	while (*s && ft_isdigit(*s))
		s++;
	if (*s != delim || s == start)
		return (NULL);
	while (*s == delim)
		s++;
	return (s);
}
