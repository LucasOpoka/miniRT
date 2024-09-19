/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:47:23 by atorma            #+#    #+#             */
/*   Updated: 2024/09/19 21:26:02 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../includes/ppm.h"

int			ppm_matrix_alloc(t_ppm *ppm);
int			parse_header(t_ppm *ppm);

static void	pixel_set(t_ppm *ppm, uint32_t x, uint32_t y, uint32_t offset)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = ppm->data[offset];
	g = ppm->data[offset + 1];
	b = ppm->data[offset + 2];
	ppm->colors[y][x].r = (double)r / 255;
	ppm->colors[y][x].g = (double)g / 255;
	ppm->colors[y][x].b = (double)b / 255;
}

static void	parse_pixel_data(t_ppm *ppm)
{
	const uint32_t	start = ppm->line - ppm->data;
	uint32_t		x;
	uint32_t		y;
	uint32_t		offset;

	y = 0;
	while (y < ppm->height)
	{
		x = 0;
		while (x < ppm->width)
		{
			offset = (y * ppm->width * 3) + (x * 3) + start;
			pixel_set(ppm, x, y, offset);
			x++;
		}
		y++;
	}
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
	if (!ppm_matrix_alloc(ppm))
		return (0);
	parse_pixel_data(ppm);
	return (1);
}

int	ppm_load(char *file, t_ppm *ppm)
{
	char	*data;

	ft_bzero(ppm, sizeof(t_ppm));
	data = file_load(file, &ppm->data_size, e_file_ppm);
	if (!data)
	{
		return (0);
	}
	if (!ppm_parse(ppm, data))
	{
		ppm_matrix_free(ppm);
		free(data);
		return (0);
	}
	free(data);
	return (1);
}
