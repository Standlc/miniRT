#include "miniRT.h"

Vector	plane_normal(t_material *obj, Vector *ray_dir, Vector *hit_point)
{
	Vector	normal;

	normal = ((t_plane *)(obj->shape))->normal;
	if (dot(normal, *ray_dir) > 0)
		return (scale(normal, -1));
	return (normal);
}

int	intersect_plane(Ray *ray, t_material *obj, double *t)
{
	double	d;
	double	n_ray_dot;
	t_plane	*plane;

	plane = (t_plane *)(obj->shape);
	n_ray_dot = dot(plane->normal, ray->dir);
	if (n_ray_dot == 0)
		return (0);
	d = dot(plane->normal, plane->point);
	*t = (d - dot(plane->normal, ray->origin)) / n_ray_dot;
	return (*t > ZERO);
}

// int	intersect_triangle(t_tri triangle, Ray ray, double *t)
// {
// 	Vector	intersection;
// 	Vector	edge;
// 	Vector	v_to_intersection;

// 	if (!intersect_plane(&ray, &triangle.plane, t))
// 		return (0);
// 	intersection = get_line_point(ray, *t);
// 	Vector	normal = triangle.plane.normal;

// 	edge = vect_op(triangle.a, '-', triangle.b);
// 	v_to_intersection = vect_op(intersection, '-', triangle.b);
// 	if (dot(normal, cross_product(edge, v_to_intersection)) < 0)
// 		return (0);

// 	edge = vect_op(triangle.b, '-', triangle.c);
// 	v_to_intersection = vect_op(intersection, '-', triangle.c);
// 	if (dot(normal, cross_product(edge, v_to_intersection)) < 0)
// 		return (0);

// 	edge = vect_op(triangle.c, '-', triangle.a);
// 	v_to_intersection = vect_op(intersection, '-', triangle.a);
// 	if (dot(normal, cross_product(edge, v_to_intersection)) < 0)
// 		return (0);
// 	return (1);
// }