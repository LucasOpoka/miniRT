
#include "../../includes/miniRT.h"
#include "../../includes/ppm.h"

int	ppm_matrix_alloc(t_ppm *ppm);

static char *line_next(t_ppm *ppm)
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
	//printf("ppm->ptr: %d", ppm->ptr);
	write(1, ppm->line, (newline - ppm->line) + 1);
}

int atoi_safe(char  *s, int max)
{
	long long   res;
	char	    *start;

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
		return (-1);
	if (s == start)
		return (-1);
	return (res);
}

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

static int  parse_header_entry(t_ppm *ppm)
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

static int  parse_header(t_ppm *ppm)
{

	while (ppm->line && *ppm->line)
	{
		if (ppm->ptr == 3)	
			break ;
		if (*ppm->line != '#' && !parse_header_entry(ppm))
			return (0);
		ppm->line = line_next(ppm);
	}
	if (ppm->width <= 0 || ppm->height <= 0)
		return (0);
	if (ppm->max_color <= 0)
		return (0);
	return (ppm->ptr == 3);
}

static char  *skip_color(char *s, int delim)
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

static int  fill_rgb(t_ppm *ppm, t_clr *col, char *s, int i)
{
	double	res;

	res = atoi_safe(s, ppm->max_color);
	if (res < 0)
	{
		printf("res: %f\n", res);
		return (0);
	}
	res /= 255;
	if (i == 0)
		col->r = res;
	if (i == 1)
		col->g = res;
	if (i == 2)
		col->b = res;
	return (1);
}

static int  fill_pixels(t_ppm *ppm, int y)
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
		s = skip_color(s, ' ');
		i++;
	}
	return (x == ppm->width);
}

static int  parse_pixels(t_ppm *ppm)
{
	int y;

	y = 0;
	while (ppm->line && *ppm->line)
	{
		if (*ppm->line != '#')
		{
			line_print(ppm);
			if (!fill_pixels(ppm, y))
				return (0);
			y++;
		}
		ppm->line = line_next(ppm);
	}
	return (ppm->height == y);
}

int	ppm_parse(char	*s)
{
	t_ppm	ppm;

	if (ft_strncmp("P3\n", s, 3) != 0)
		return (0);
	ppm.ptr = 0;
	ppm.data = s;
	ppm.line = s;
	if (!parse_header(&ppm))
		return (0);
	printf("ppm.width: %d\n", ppm.width);
	printf("ppm.height: %d\n", ppm.height);
	printf("ppm.max_color: %d\n", ppm.max_color);
	if (!ppm_matrix_alloc(&ppm))
		return (0);
	printf("ppm->colors matrix allocated\n");
	if (!parse_pixels(&ppm))
		return (0);
	printf("pixels parsed\n");
	return (1);
}

void	ppm_load(char	*file)
{
	char	*data;

	data = file_load(file, e_file_ppm);
	if (!data)
	{
		printf("could not load ppm!\n");
		return ;
	}
	if (!ppm_parse(data))
		printf("ppm_parse error\n");
	free(data);
}
