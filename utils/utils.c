#include "minirt.h"

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

double  max(double a, double b)
{
	if (a < b)
		return (b);
	return (a);
}
