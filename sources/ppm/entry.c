
#include "../../includes/miniRT.h"
#include "../../includes/ppm.h"

int	atoi_safe(char  *s, int max);
char	*line_next_pixel(char *s, int delim);

static char  *skip_digits(char *s, int expected)
{
	const char *start = s;

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


static int  fill_rgb(t_ppm *ppm, t_clr *col, char *s, int i)
{
	double	res;

	res = atoi_safe(s, ppm->max_color);
	if (res < 0)
		return (0);
	res /= 255;
	if (i == 0)
		col->r = res;
	if (i == 1)
		col->g = res;
	if (i == 2)
		col->b = res;
	return (1);
}

int  parse_header_entry(t_ppm *ppm)
{
	char	*s;

	s = ppm->line;
	if (ppm->ptr == 1)
	{
		ppm->width = ft_atoi(s);
		s = skip_digits(s, ' ');
		if (!s)
			return (0);
		s++;
		ppm->height = ft_atoi(s);
		if (!skip_digits(s, '\n'))
			return (0);
	}
	if (ppm->ptr == 2)
	{
		if (!skip_digits(s, '\n'))
			return (0);
		ppm->max_color = atoi_safe(s, 65536);
	}
	return (1);
}

int  parse_pixel_entry(t_ppm *ppm, int y)
{
	int	x;
	int	i;
	char	*s;

	x = 0;
	i = 0;
	s = ppm->line;
	while (s && *s && *s != '\n')
	{
		if (i > 2)
			i = 0;
		if (!fill_rgb(ppm, &ppm->colors[y][x], s, i))
			return (0);
		if (i == 2)
		{
			printf("color.r: %f\n", ppm->colors[y][x].r);
			printf("color.g: %f\n", ppm->colors[y][x].g);
			printf("color.b: %f\n", ppm->colors[y][x].b);
			x++;
		}
		s = line_next_pixel(s, ' ');
		i++;
	}
	return (x == ppm->width);
}
