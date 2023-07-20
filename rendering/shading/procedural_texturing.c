#include "minirt.h"

float	checkers(t_vec2 point, float scale)
{
	float	pattern;

	pattern = (
			cosf(point.x * 2 * M_PI * scale)
			* 
			sinf(point.y * 2 * M_PI * scale)
			+ 1.f) / 2.f;

	return (roundf(pattern));
}
