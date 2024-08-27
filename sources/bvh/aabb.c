
#include "../../includes/miniRT.h"
#include <math.h>

int aabb_raycast(t_ray ray, float bmin[3], float bmax[3])
{
    t_vct   rd;
    rd.x = 1.0 / ray.D.x;
    rd.y = 1.0 / ray.D.y;
    rd.z = 1.0 / ray.D.z;
    float t1 = (bmin[0] - ray.O.x) * rd.x;
    float t2 = (bmax[0] - ray.O.x) * rd.x;
    float t3 = (bmin[1] - ray.O.y) * rd.y;
    float t4 = (bmax[1] - ray.O.y) * rd.y;
    float t5 = (bmin[2] - ray.O.z) * rd.z;
    float t6 = (bmax[2] - ray.O.z) * rd.z;

    float tmin = fmaxf(fmaxf(fminf(t1, t2), fminf(t3, t4)), fminf(t5, t6));
    float tmax = fminf(fminf(fmaxf(t1, t2), fmaxf(t3, t4)), fmaxf(t5, t6));

    // if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
    if (tmax < 0)
	return (0);
    // if tmin > tmax, ray doesn't intersect AABB
    if (tmin > tmax)
	return (0);
    return (1);
    //return (tmin < tmax);
}
