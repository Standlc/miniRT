#include "minirt.h"

int	create_sphere(t_material *obj, float radius, t_vec center, int procedural_texturing)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (1);

	sphere->center = center;
	sphere->radius = radius;
	obj->shape = (void *)sphere;
	obj->intersect = intersect_sphere;
	obj->normal = sphere_normal;
	obj->light_sample = sample_sphere;
	if (procedural_texturing)
		obj->procedural_texturing = sphere_pattern;
	else
		obj->procedural_texturing = NULL;
	return (0);
}

float	sphere_pattern(void *shape, t_ray *normal)
{
	float		u;
	float		v;
	float		pattern;
	int			scale;
	
	u = (1 + atan2(normal->dir.z, normal->dir.x) / M_PI) * 0.5;
	v = acosf(normal->dir.y) / M_PI;

	scale = 10;
	pattern = (
		cos(u * 2 * M_PI * scale)
		*
		sin(v * 2 * M_PI * scale)
		 + 1) * 0.5;

	pattern = roundf(pattern);
	return (pattern);
}

int	solve_quadratic(t_quadratic f, double *t_1, double *t_2)
{
	double	discr;
	double	res;

	discr = (f.b * f.b) - 4 * f.a * f.c;
	if (discr < 0)
		return (0);
	if (discr == 0)
	{
		*t_1 = - 0.5 * f.b / f.a;
		*t_2 = *t_1;
	}
	else
	{
		res = (f.b > 0) ? -0.5 * (f.b + sqrt(discr)) : -0.5 * (f.b - sqrt(discr));
		*t_1 = res / f.a;
		*t_2 = f.c / res;
	}
	return (1);
}

int	intersect_sphere(t_ray *ray, void *shape, double *t)
{
	t_quadratic	f;
	t_sphere	*sphere;
	double		t_1;
	double		t_2;
	t_vec		w;

	sphere = (t_sphere *)shape;
	w = sub(ray->origin, sphere->center);
	f.a = dot(ray->dir, ray->dir);
	f.b = 2 * dot(ray->dir, w);
	f.c = dot(w, w) - pow(sphere->radius, 2);
	if (!solve_quadratic(f, &t_1, &t_2))
		return (0);
	*t = get_closest_intersection(t_1, t_2);
	return (*t > 0.0);
}

t_vec	sample_sphere(void *shape, t_ray *normal)
{
	t_sphere	*sphere;
	t_vec		sample_dir;

	sphere = (t_sphere *)shape;
	sample_dir = scale(random_dir(), sphere->radius);
	if (dot(sample_dir, normal->dir) < 0)
		sample_dir = scale(sample_dir, -1);
	return (add(sample_dir, sphere->center));
}

t_vec	sphere_normal(void *shape, t_vec *ray_dir, t_vec *hit_point)
{
	t_vec	normal;

	normal = normalize(sub(*hit_point, ((t_sphere *)shape)->center));
	if (dot(normal, *ray_dir) > 0)
		return (scale(normal, -1));
	return (normal);
}
