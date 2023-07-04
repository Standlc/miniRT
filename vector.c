#include "miniRT.h"

double dot(Vector v1, Vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

Vector    scale(Vector v, double coef)
{
	// v.x *= coef;
	// v.y *= coef;
	// v.z *= coef;
	// return (v);
	return ((Vector){v.x * coef, v.y * coef, v.z * coef});
}

double  vector_len(Vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

Vector	normalize(Vector v)
{
    double  len;

    len = vector_len(v);
    if (len == 0)
        return (v);
	return (scale(v, 1 / len));
}

Vector	add(Vector v1, Vector v2)
{
	// v1.x += v2.x;
	// v1.y += v2.y;
	// v1.z += v2.z;
	// return (v1);
	return ((Vector){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

Vector	minus(Vector v1, Vector v2)
{
	// v1.x -= v2.x;
	// v1.y -= v2.y;
	// v1.z -= v2.z;
	// return (v1);
	return ((Vector){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

Vector	mult(Vector v1, Vector v2)
{
	// v1.x *= v2.x;
	// v1.y *= v2.y;
	// // v1.z *= v2.z;
	// return (v1);
	return ((Vector){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z});
}

Vector    vect_op(Vector v1, char operation, Vector v2)
{
	if (operation == '+')
		return ((Vector){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
	else if (operation == '-')
		return ((Vector){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
	else if (operation == '*')
		return ((Vector){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z});
	return (v1);
}

Vector  get_reflection(Vector *v, Vector *normal)
{
	return (minus(*v, scale(*normal, 2 * dot(*v, *normal))));
}

Vector	cross_product(Vector v1, Vector v2)
{
	Vector	res;

	res.x = (v1.y * v2.z) - (v1.z * v2.y);
	res.y = - ((v1.x * v2.z) - (v1.z * v2.x));
	res.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (normalize(res));
}

Vector  get_line_point(Ray ray, double d)
{
	ray.dir.x = ray.dir.x * d + ray.origin.x;
	ray.dir.y = ray.dir.y * d + ray.origin.y;
	ray.dir.z = ray.dir.z * d + ray.origin.z;
	return (ray.dir);
}
