
#include "../../includes/miniRT.h"
#include "../../includes/ppm.h"

static int	atoi_safe(char *s, int max)
{
	long long	res;
	char		*start;

	res = 0;
	start = s;
	if (max <= 0)
		max = 3840 * 2160;
	while (*s)
	{
		if (!ft_isdigit(*s))
			break ;
		res = res * 10 + (*s - '0');
		if (res > max)
			return (-1);
		s++;
	}
	if (*s && *s != ' ' && *s != '\n')
		return (0);
	if (s == start)
		return (0);
	return (res);
}

static char	*skip_digits(char *s, int expected)
{
	const char	*start = s;

	if (*s == '0')
		return (NULL);
	while (*s && ft_isdigit(*s))
		s++;
	if (*s != expected || s == start)
		return (NULL);
	if (*s && *(s + 1))
	{
		if (*s == *(s + 1))
			return (NULL);
	}
	return (s);
}

static char	*line_next(t_ppm *ppm)
{
	char	*newline;

	newline = ft_strchr(ppm->line, '\n');
	if (!newline)
		return (NULL);
	if (*ppm->line == '#')
		return (newline + 1);
	ppm->ptr += 1;
	return (newline + 1);
}

static int  parse_header_entry(t_ppm *ppm)
{
	char	*s;

	s = ppm->line;
	if (ppm->ptr == 1)
	{
		ppm->width = atoi_safe(s, 65536);
		s = skip_digits(s, ' ');
		if (ppm->width <= 0 || !s)
			return (0);
		s++;
		ppm->height = atoi_safe(s, 65536);
		if (ppm->height <= 0 || !skip_digits(s, '\n'))
			return (0);
	}
	if (ppm->ptr == 2)
	{
		if (!skip_digits(s, '\n'))
			return (0);
		ppm->max_color = atoi_safe(s, 255);
	}
	return (1);
}

int	parse_header(t_ppm *ppm)
{
	size_t	blob_size;

	while (ppm->line && *ppm->line)
	{
		if (ppm->ptr == 3)
			break ;
		if (*ppm->line != '#' && !parse_header_entry(ppm))
			return (0);
		ppm->line = line_next(ppm);
	}
	if (ppm->width <= 0 || ppm->height <= 0 || ppm->max_color <= 0)
		return (0);
	blob_size = ppm->data_size - (ppm->line - ppm->data);
	if (blob_size != (3 * ppm->height * ppm->width))
		return (0);
	return (ppm->ptr == 3);
}
