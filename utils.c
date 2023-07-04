#include "miniRT.h"

double	relu(double n)
{
	if (n > 0.0)
		return (n);
	return (0.0);
}

double  min(double a, double b)
{
	if (a > b)
		return (b);
	return (a);
}

float	randf()
{
	return ((float)rand() / RAND_MAX);
}

float	normal_randf()
{
	float	theta = 2 * M_PI * randf();
    float	rho = sqrt(-2 * log(randf()));
    return (rho * cos(theta));
}
