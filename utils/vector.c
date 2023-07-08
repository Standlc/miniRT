#include "../miniRT.h"

t_vec	project(t_vec projected, t_vec ref)
{
	return (scale(ref, dot(projected, ref) / dot(ref, ref)));
}

double dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec    scale(t_vec v, double coef)
{
	v.x *= coef;
	v.y *= coef;
	v.z *= coef;
	return (v);
	// return ((t_vec){v.x * coef, v.y * coef, v.z * coef});
}

double  vec_len(t_vec v)
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
	// return ((t_vec){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_vec	sub(t_vec v1, t_vec v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return (v1);
	// return ((t_vec){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

t_vec	mult(t_vec v1, t_vec v2)
{
	v1.x *= v2.x;
	v1.y *= v2.y;
	// v1.z *= v2.z;
	return (v1);
	// return ((t_vec){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z});
}

t_vec    vect_op(t_vec v1, char operation, t_vec v2)
{
	if (operation == '+')
		return ((t_vec){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
	else if (operation == '-')
		return ((t_vec){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
	else if (operation == '*')
		return ((t_vec){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z});
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

t_vec  get_ray_point(Ray ray, double d)
{
	ray.dir.x = ray.dir.x * d + ray.origin.x;
	ray.dir.y = ray.dir.y * d + ray.origin.y;
	ray.dir.z = ray.dir.z * d + ray.origin.z;
	return (ray.dir);
}
