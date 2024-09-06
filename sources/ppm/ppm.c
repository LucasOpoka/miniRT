
#include "../../includes/miniRT.h"
#include "../../includes/ppm.h"

int	ppm_matrix_alloc(t_ppm *ppm);
char	*line_next(t_ppm *ppm);
void	line_print(t_ppm *ppm);
char	*line_next_pixel(char *s, int delim);
int	parse_header_entry(t_ppm *ppm);
int	parse_pixel_entry(t_ppm *ppm, int y);

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

static int  parse_pixels(t_ppm *ppm)
{
	int y;

	y = 0;
	while (ppm->line && *ppm->line)
	{
		if (*ppm->line != '#')
		{
			line_print(ppm);
			if (!parse_pixel_entry(ppm, y))
				return (0);
			y++;
		}
		ppm->line = line_next(ppm);
	}
	return (ppm->height == y);
}

static int  ppm_parse(t_ppm *ppm, char *data)
{
	if (ft_strncmp("P3\n", data, 3) != 0)
		return (0);
	ppm->ptr = 0;
	ppm->data = data;
	ppm->line = data;
	if (!parse_header(ppm))
		return (0);
	printf("ppm->width: %d\n", ppm->width);
	printf("ppm->height: %d\n", ppm->height);
	printf("ppm->max_color: %d\n", ppm->max_color);
	if (!ppm_matrix_alloc(ppm))
		return (0);
	if (!parse_pixels(ppm))
		return (0);
	printf("pixels parsed\n");
	return (1);
}

int	ppm_load(char	*file)
{
	t_ppm	ppm;
	char	*data;

	data = file_load(file, e_file_ppm);
	if (!data)
	{
		printf("could not load ppm file!\n");
		return (0);
	}
	ft_bzero(&ppm, sizeof(t_ppm));
	if (!ppm_parse(&ppm, data))
	{
		printf("ppm_parse error\n");
		ppm_matrix_free(&ppm);
		free(data);
		return (0);
	}
	free(data);
	return (1);
}
