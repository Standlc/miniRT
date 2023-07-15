#include "minirt.h"

float	uv_pattern(float u, float v, float scale)
{
	float	pattern;

	pattern = (
			cosf(u * 2 * M_PI * scale)
			* 
			sinf(v * 2 * M_PI * (scale))
			+ 1.f) / 2.f;
	return (roundf(pattern));
}