/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:47:23 by atorma            #+#    #+#             */
/*   Updated: 2024/09/09 20:24:56 by lopoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../includes/ppm.h"

int			ppm_matrix_alloc(t_ppm *ppm);
char		*line_next(t_ppm *ppm);
void		line_print(t_ppm *ppm);
char		*line_next_pixel(char *s, int delim);
int			parse_header_entry(t_ppm *ppm);
int			parse_pixel_entry(t_ppm *ppm, int y);

int	atoi_safe(char *s, int max)
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
		return (-1);
	if (s == start)
		return (-1);
	return (res);
}

static int	parse_header(t_ppm *ppm)
{
	long	blob_size;

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
	printf("data_size: %zu, %d\n",
			ppm->data_size - (ppm->line - ppm->data),
			3 * ppm->height * ppm->width);
	return (ppm->ptr == 3);
}

static int	parse_pixels(t_ppm *ppm)
{
	const uint32_t    start = ppm->line - ppm->data;
	uint32_t    x;
	uint32_t    y;

	y = 0;
	while (y < ppm->height)
	{
		x = 0;
		while (x < (ppm->width))
		{
			if (x % 3 == 0)
			{
				uint32_t    offset = (y * ppm->width) + (x * 3) + start;
				unsigned char r = ppm->data[offset];
				unsigned char g = ppm->data[offset + 1];
				unsigned char b = ppm->data[offset + 2];
				ppm->colors[y][x].r = (double)r / 255;
				ppm->colors[y][x].g = (double)g / 255;
				ppm->colors[y][x].b = (double)b / 255;
				/*
				printf("[%u][%u]\n", y, x);
				printf("%02x", r);
				printf("%02x", g);
				printf("%02x", b);
				*/
			}
			x++;
		}
		y++;
	}
	printf("y: %u\n", y);
	printf("x: %u\n", x);
	printf("x * y: %u\n", (x - start) * y);
	return (ppm->height == y);
}

static int	ppm_parse(t_ppm *ppm, char *data)
{
	ppm->ptr = 0;
	ppm->data = data;
	ppm->line = data;
	if (ft_strncmp("P6\n", data, 3) != 0)
		return (0);
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

int	ppm_load(char *file, t_ppm *ppm)
{
	char	*data;

	ft_bzero(ppm, sizeof(t_ppm));
	data = file_load(file, &ppm->data_size, e_file_ppm);
	if (!data)
	{
		printf("could not load ppm file!\n");
		return (0);
	}
	if (!ppm_parse(ppm, data))
	{
		printf("ppm_parse error\n");
		ppm_matrix_free(ppm);
		free(data);
		return (0);
	}
	free(data);
	return (1);
}
