
#include "../../includes/miniRT.h"
#include "../../includes/ppm.h"

int ppm_matrix_alloc(t_ppm *ppm)
{
	int y;

	ppm->colors = (t_clr **)malloc(ppm->height * sizeof(t_clr *));
	if (!ppm->colors)
		return (0);
	y = 0;
	while (y < ppm->height)
	{
		ppm->colors[y] = malloc(ppm->width * sizeof(t_clr));
		if (!ppm->colors[y])
		{
			while (--y >= 0)
				free(ppm->colors[y]);
			free(ppm->colors);
			return (0);
		}
		y++;
	}
	return (1);
}

void	ppm_matrix_free(t_ppm *ppm)
{
	int y;

	if (!ppm->colors)
		return ;
	y = ppm->height;
	while (--y >= 0)
		free(ppm->colors[y]);
	free(ppm->colors);
}
