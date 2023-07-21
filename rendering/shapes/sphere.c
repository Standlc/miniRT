#include "minirt.h"

// 182,148,128
// 235,143,138

t_vec2	sphere_texture_coordinates(t_hit_info *hit, int keep_ratio)
{
	t_vec2	coordinates;

	(void)keep_ratio;
	coordinates.x = atan2(hit->normal.z, hit->normal.x) / M_PI + 1;
	coordinates.y = acosf(hit->normal.y) / M_PI;
	return (coordinates);
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
		if (f.b > 0)
			res = -0.5 * (f.b + sqrt(discr));
		else
			res = -0.5 * (f.b - sqrt(discr));
		*t_1 = res / f.a;
		*t_2 = f.c / res;
	}
	return (1);
}

int	intersect_sphere(t_ray *ray, void *shape, double *t, int *is_surface_hit)
{
	t_quadratic	f;
	t_sphere	*sphere;
	double		t_1;
	double		t_2;
	t_vec		w;

	(void)is_surface_hit;
	sphere = (t_sphere *)shape;
	w = sub(ray->origin, sphere->center);
	f.a = 1.0;
	f.b = 2 * dot(ray->dir, w);
	f.c = dot(w, w) - pow(sphere->radius, 2);
	if (!solve_quadratic(f, &t_1, &t_2))
		return (0);
	*t = get_closest_intersection(t_1, t_2);
	return (*t > 0.0);
}

t_vec	sample_sphere(void *shape, t_vec *normal_dir)
{
	t_sphere	*sphere;
	t_vec		sample_dir;

	(void)normal_dir;
	sphere = (t_sphere *)shape;
	sample_dir = scale(random_dir(), sphere->radius);
	return (add(sample_dir, sphere->center));
}

t_vec	sphere_normal(t_hit_info *hit)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)(hit->obj.shape);
	return (normalize(sub(hit->hit_point, sphere->center)));
}

int	create_sphere(t_material *obj, t_info *info)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (1);
	sphere->center = info->center;
	sphere->radius = info->radius;
	obj->shape = (void *)sphere;
	obj->intersect = intersect_sphere;
	obj->normal = sphere_normal;
	obj->texture_coordinates = sphere_texture_coordinates;
	if (info->bump_mapping)
		obj->texture = BUMP_MAP;
	if (info->procedural_texturing)
		obj->texture = CHECKERS;
	return (0);
}
