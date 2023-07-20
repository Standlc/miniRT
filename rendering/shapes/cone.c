#include "minirt.h"

t_vec2	cone_base_pattern(t_cone *cone, t_vec *center_to_hitpoint, int keep_ratio)
{
	t_vec2	point;

	point.x = get_angle(center_to_hitpoint, &(cone->system.x)) / 180;
	point.y = vec_len(*center_to_hitpoint) / cone->radius;
	if (keep_ratio)
		point.y /= cone->circumference / cone->radius / 2;
	return (point);
}

t_vec2	cone_surface_pattern(t_cone *cone, t_vec *center_to_hitpoint, t_vec *hitpoint, int keep_ratio)
{
	t_vec	projected;
	t_vec	projected_to_hitpoint;
	float	height_from_base;
	t_vec2	point;

	projected = project(*center_to_hitpoint, cone->dir);
	projected_to_hitpoint = sub(*hitpoint, add(cone->center, projected));
	point.x = get_angle(&projected_to_hitpoint, &(cone->system.x)) / 180;
	height_from_base = dot(*center_to_hitpoint, cone->dir);
	point.y = (height_from_base / cone->height);
	if (keep_ratio)
		point.y *= 2 / (cone->circumference / cone->height);
	return (point);
}

t_vec2	cone_texture_coordinates(t_hit_info *hit, int keep_ratio)
{
	t_cone		*cone;
	t_vec		center_to_hitpoint;

	cone = (t_cone *)(hit->obj.shape);
	center_to_hitpoint = sub(hit->hit_point, cone->center);
	if (hit->is_surface_hit)
		return (cone_base_pattern(cone, &center_to_hitpoint, keep_ratio));
	return (cone_surface_pattern(cone, &center_to_hitpoint, &(hit->hit_point), keep_ratio));
}

int	check_cone_surface_intersection(t_cone *cone, t_vec hit_point, double *t)
{
	if (*t <= ZERO)
		return (0);
	if (dot(sub(hit_point, cone->center), cone->dir) <= cone->height)
		return (1);
	*t = -1;
	return (0);
}

int	check_below_cone_intersection(t_cone *cone, t_vec hit_point, double *t)
{
	if (*t <= ZERO)
		return (0);
	if (dot(sub(hit_point, cone->center), cone->dir) > 0.0)
		return (1);
	*t = -1;
	return (0);
}

int	intersect_cone(t_ray *ray, void *shape, double *t, int *is_surface_hit)
{
	t_quadratic	f;
	t_cone		*cone;
	double		t_1;
	double		t_2;
	double		t_base;

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

	f.a = 1 - m * pow(dot_ray_dir_h, 2) - pow(dot_ray_dir_h, 2);
	f.b = 2 * (dot(ray->dir, w) - m * dot_ray_dir_h * dot_w_h - dot_ray_dir_h * dot_w_h);
	f.c = dot(w, w) - m * dot_w_h_squared - dot_w_h_squared;

	if (!solve_quadratic(f, &t_1, &t_2))
		return (0);

	check_cone_surface_intersection(cone, get_ray_point(*ray, t_1), &t_1);
	check_cone_surface_intersection(cone, get_ray_point(*ray, t_2), &t_2);
	*t = get_closest_intersection(t_1, t_2);

	check_below_cone_intersection(cone, get_ray_point(*ray, *t), t);

	intersect_circle(ray, (void *)&(cone->base), &t_base, NULL);
	*t = get_closest_intersection(*t, t_base);

	if (is_surface_hit != NULL)
		*is_surface_hit = *t == t_base;
	return (*t > 0.0);
}

t_vec	cone_normal(t_hit_info *hit)
{
	t_cone	*cone;
	t_vec	top_to_hitpoint_dir;

	cone = (t_cone *)(hit->obj.shape);

	if (hit->is_surface_hit)
		return (cone->base.plane.normal);

	top_to_hitpoint_dir = sub(hit->hit_point, cone->top);
	return (cross_product(cross_product(top_to_hitpoint_dir, cone->dir), top_to_hitpoint_dir));
}

int	create_cone(t_material *obj, t_info *info)
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
	cone->base.radius = info->radius;
	cone->base.plane.normal = scale(cone->dir, -1);
	cone->base.plane.point = info->center;
	cone->system = create_system(info->dir);
	cone->circumference = 2 * M_PI * info->radius;

	obj->shape = (void *)cone;
	obj->intersect = intersect_cone;
	obj->normal = cone_normal;
	obj->texture_coordinates = cone_texture_coordinates;
	if (info->bump_mapping)
		obj->texture = BUMP_MAP;
	if (info->procedural_texturing)
		obj->texture = CHECKERS;
	return (0);
}
