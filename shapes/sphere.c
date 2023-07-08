#include "../miniRT.h"

int solve_quadratic(Quadratic_fun f, double *x1, double *x2)
{
	double  discr;
	double  res;

	discr = (f.b * f.b) - 4 * f.a * f.c;
	if (discr < 0)
		return (0);
	if (discr == 0)
	{
		*x1 = - 0.5 * f.b / f.a;
		*x2 = *x1;
	}
	else
	{
		res = (f.b > 0) ? -0.5 * (f.b + sqrt(discr)) : -0.5 * (f.b - sqrt(discr));
		*x1 = res / f.a;
		*x2 = f.c / res;
	}
	return (1);
}

int	intersect_sphere(Ray *ray, void *shape, double *t)
{
	Quadratic_fun   f;
	double          intersect1;
	double          intersect2;
	t_sphere		*sphere;

    sphere = (t_sphere *)shape;
	t_vec  L = sub(ray->origin, sphere->center);
	f.a = dot(ray->dir, ray->dir);
	f.b = 2 * dot(ray->dir, L);
	f.c = dot(L, L) - (sphere->radius * sphere->radius);
	if (!solve_quadratic(f, &intersect1, &intersect2))
		return (0);
	*t = get_closest_intersection(intersect1, intersect2);
	return (*t > 0);
}

t_vec	sample_sphere(void *shape)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)shape;
	return (add(scale(random_dir(), sphere->radius), sphere->center));
}

t_vec	sphere_normal(void *shape, t_vec *ray_dir, t_vec *hit_point)
{
	t_vec	normal;

	normal = normalize(sub(*hit_point, ((t_sphere *)shape)->center));
	if (dot(normal, *ray_dir) > 0)
		return (scale(normal, -1));
	return (normal);
}
