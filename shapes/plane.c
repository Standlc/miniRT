#include "minirt.h"

int	create_plane(t_material *obj, t_vec center, t_vec dir, int procedural_texturing)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (1);
	plane->point = center;
	plane->normal = normalize(dir);

	plane->system = create_system(plane->normal);

	obj->shape = (void *)plane;
	obj->intersect = intersect_plane;
	obj->normal = plane_normal;
	if (procedural_texturing)
		obj->procedural_texturing = plane_pattern;
	else
		obj->procedural_texturing = NULL;
	return (0);
}

float	plane_pattern(void *shape, t_ray *normal)
{
	float		u;
	float		v;
	int			scale;
	float		pattern;

	t_plane	*plane;
	plane = (t_plane *)shape;

	u = dot(normal->origin, plane->system.x);
	v = dot(normal->origin, plane->system.z);

	scale = 2;
	pattern = (cos(u * scale) * sin(v * scale) + 1) * 0.5;
	return (roundf(pattern));
}

t_vec	plane_normal(void *shape, t_vec *ray_dir, t_vec *hit_point)
{
	t_vec	normal;

	(void)hit_point;
	normal = ((t_plane *)shape)->normal;
	if (dot(normal, *ray_dir) > 0)
		return (scale(normal, -1));
	return (normal);
}

int	intersect_plane(t_ray *ray, void *shape, double *t)
{
	double	d;
	double	n_ray_dot;
	t_plane	*plane;

	plane = (t_plane *)shape;
	n_ray_dot = dot(plane->normal, ray->dir);
	if (n_ray_dot == 0.0)
		return (0);
	d = dot(plane->normal, plane->point);
	*t = (d - dot(plane->normal, ray->origin)) / n_ray_dot;
	return (*t > ZERO);
}

// int	intersect_triangle(t_tri triangle, t_ray ray, double *t)
// {
// 	t_vec	intersection;
// 	t_vec	edge;
// 	t_vec	v_to_intersection;

// 	if (!intersect_plane(&ray, &triangle.plane, t))
// 		return (0);
// 	intersection = get_ray_point(ray, *t);
// 	t_vec	normal = triangle.plane.normal;

// 	edge = sub(triangle.a, triangle.b);
// 	v_to_intersection = sub(intersection, triangle.b);
// 	if (dot(normal, cross_product(edge, v_to_intersection)) < 0)
// 		return (0);

// 	edge = sub(triangle.b, triangle.c);
// 	v_to_intersection = sub(intersection, triangle.c);
// 	if (dot(normal, cross_product(edge, v_to_intersection)) < 0)
// 		return (0);

// 	edge = sub(triangle.c, triangle.a);
// 	v_to_intersection = sub(intersection, triangle.a);
// 	if (dot(normal, cross_product(edge, v_to_intersection)) < 0)
// 		return (0);
// 	return (1);
// }