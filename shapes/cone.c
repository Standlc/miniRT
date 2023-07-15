#include "minirt.h"

int	create_cone(t_material *object, t_info *info)
{
	t_cone	*cone;

	cone = malloc(sizeof(t_cone));
	if (!cone)
		return (1);
	cone->center = info->center;
	cone->radius = info->radius;
	cone->height = info->height;
	cone->dir = normalize(info->dir);
	cone->top = add(info->center, scale(cone->dir, info->height));

	cone->bottom.radius = info->radius;
	cone->bottom.plane.normal = scale(cone->dir, -1);
	cone->bottom.plane.point = info->center;

	object->shape = (void *)cone;
	object->intersect = intersect_cone;
	object->normal = cone_normal;
	if (info->procedural_texturing)
		object->procedural_texturing = sphere_pattern;
	else
		object->procedural_texturing = NULL;
	return (0);
}

int	check_cone_surface_intersection(t_cone *cone, t_vec hit_point, double *t)
{
	if (*t <= 0.0)
		return (0);
	if (dot(sub(hit_point, cone->center), cone->dir) <= cone->height)
		return (1);
	*t = -1;
	return (0);
}

int	check_below_cone_intersection(t_cone *cone, t_vec hit_point, double *t)
{
	t_vec	center_to_projected;

	if (*t <= 0.0)
		return (0);
	if (dot(sub(hit_point, cone->center), cone->dir) >= 0)
		return (1);
	*t = -1;
	return (0);
}

int	intersect_cone(t_ray *ray, void *shape, double *t)
{
	t_quadratic	f;
	t_cone		*cone;
	double		t_1;
	double		t_2;
	double		t_cover;

	cone = (t_cone *)shape;

	double	m;
	t_vec	w;
	double	dot_ray_dir_h;
	double	dot_w_h;
	double	dot_w_h_squared;

	m = pow(cone->radius, 2) / pow(cone->height, 2);
	w = sub(ray->origin, cone->top);
	dot_ray_dir_h = dot(ray->dir, cone->dir);
	dot_w_h = dot(w, cone->dir);
	dot_w_h_squared = pow(dot_w_h, 2);

	f.a = dot(ray->dir, ray->dir) - m * pow(dot_ray_dir_h, 2) - pow(dot_ray_dir_h, 2);
	f.b = 2 * (dot(ray->dir, w) - m * dot_ray_dir_h * dot_w_h - dot_ray_dir_h * dot_w_h);
	f.c = dot(w, w) - m * dot_w_h_squared - dot_w_h_squared;

	if (!solve_quadratic(f, &t_1, &t_2))
		return (0);

	check_cone_surface_intersection(cone, get_ray_point(*ray, t_1), &t_1);
	check_cone_surface_intersection(cone, get_ray_point(*ray, t_2), &t_2);
	*t = get_closest_intersection(t_1, t_2);

	check_below_cone_intersection(cone, get_ray_point(*ray, *t), t);

	intersect_cirlce(ray, (void *)&(cone->bottom), &t_cover);
	*t = get_closest_intersection(*t, t_cover);
	return (*t > 0.0);
}

t_vec	cone_normal(void *shape, t_vec *ray_dir, t_vec *hit_point)
{
	t_vec	normal;
	t_cone	*cone;
	t_vec	top_to_hitpoint_dir;

	cone = (t_cone *)shape;
	top_to_hitpoint_dir = sub(*hit_point, cone->top);

	if (dot(sub(*hit_point, cone->center), cone->dir) <= ZERO)
		normal = cone->bottom.plane.normal;
	else
		normal = cross_product(cross_product(top_to_hitpoint_dir, cone->dir), top_to_hitpoint_dir);

	if (dot(normal, *ray_dir) > 0)
		return (scale(normal, -1));
	return (normal);
}
