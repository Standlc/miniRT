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

float	randf()
{
	return ((float)rand() / RAND_MAX);
}

float	normal_randf()
{
	float	theta;
	float	rho;

	theta = 2 * M_PI * randf();
	rho = sqrt(-2 * log(randf()));
    return (rho * cos(theta));
}

t_vec	random_dir()
{
	return (normalize((t_vec){normal_randf(), normal_randf(), normal_randf()}));
}
