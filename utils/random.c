#include "minirt.h"

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

t_vec	cosine_hemisphere_dir(t_vec *normal_dir)
{
	return (normalize(add(random_dir(), *normal_dir)));
}
