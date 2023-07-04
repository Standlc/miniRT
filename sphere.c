#include "miniRT.h"

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

int	intersect_sphere(Ray *ray, t_material *obj, double *intersection_t)
{
	Quadratic_fun   f;
	double          intersect1;
	double          intersect2;
	t_sphere		*sphere;

    sphere = (t_sphere *)(obj->shape);
	Vector  L = minus(ray->origin, sphere->center);
	f.a = dot(ray->dir, ray->dir);
	f.b = 2 * dot(ray->dir, L);
	f.c = dot(L, L) - (sphere->radius * sphere->radius);
	if (!solve_quadratic(f, &intersect1, &intersect2))
		return (0);
	*intersection_t = get_closest_intersection(intersect1, intersect2);
	return (*intersection_t > 0);
}

Vector	sphere_normal(t_material *obj, Vector *ray_dir, Vector *hit_point)
{
	Vector	normal;

	normal = normalize(minus(*hit_point, ((t_sphere *)(obj->shape))->center));
	if (dot(normal, *ray_dir) > 0)
		return (scale(normal, -1));
	return (normal);
}
