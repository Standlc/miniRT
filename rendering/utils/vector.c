#include "minirt.h"

void	print_vector(t_vec v)
{
	printf("[%f, %f, %f]\n", v.x, v.y, v.z);
}

t_vec	system_transform(t_vec *v, t_system *system)
{
	t_vec	transformed;

	transformed.x = v->x * system->x.x + v->y * system->y.x + v->z * system->z.x
		+ system->origin.x;
	transformed.y = v->x * system->x.y + v->y * system->y.y + v->z * system->z.y
		+ system->origin.y;
	transformed.z = v->x * system->x.z + v->y * system->y.z + v->z * system->z.z
		+ system->origin.z;
	return (transformed);
}

float	get_angle(t_vec *v1, t_vec *v2)
{
	return (acosf(dot(*v1, *v2) / (vec_len(*v1) * vec_len(*v2))) * (180 / M_PI));
}

t_vec	project(t_vec projected, t_vec ref)
{
	return (scale(ref, dot(projected, ref) / dot(ref, ref)));
}

double	dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec	scale(t_vec v, double coef)
{
	v.x *= coef;
	v.y *= coef;
	v.z *= coef;
	return (v);
}

double	vec_len(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec	normalize(t_vec v)
{
	double  len;

	len = vec_len(v);
	if (len == 0)
		return (v);
	return (scale(v, 1 / len));
}

t_vec	add(t_vec v1, t_vec v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

t_vec	sub(t_vec v1, t_vec v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return (v1);
}

t_vec  get_reflection(t_vec *v, t_vec *normal)
{
	return (sub(*v, scale(*normal, 2 * dot(*v, *normal))));
}

t_vec	cross_product(t_vec v1, t_vec v2)
{
	t_vec	res;

	res.x = (v1.y * v2.z) - (v1.z * v2.y);
	res.y = - ((v1.x * v2.z) - (v1.z * v2.x));
	res.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (normalize(res));
}

t_vec  get_ray_point(t_ray ray, double d)
{
	ray.dir.x = ray.dir.x * d + ray.origin.x;
	ray.dir.y = ray.dir.y * d + ray.origin.y;
	ray.dir.z = ray.dir.z * d + ray.origin.z;
	return (ray.dir);
}
