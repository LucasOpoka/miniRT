#include "../../includes/miniRT.h"
#include <math.h>

void	double_set(double *f, double value)
{
	f[0] = value;
	f[1] = value;
	f[2] = value;
}

void	bounds_init(t_bounds *bounds)
{
	double_set(bounds->min, DBL_MAX);
	double_set(bounds->max, DBL_MIN);
}

void	swap_qsort(uint32_t *obj_index, int i, int j)
{
	uint32_t    tmp;

	tmp = obj_index[i];
	obj_index[i] = obj_index[j];
	obj_index[j] = tmp;
}
