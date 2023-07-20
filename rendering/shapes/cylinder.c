#include "minirt.h"

t_vec2	cylinder_cover_pattern(t_cylinder *cylinder, t_vec *hitpoint, int keep_ratio)
{
	t_vec	center_to_hitpoint;
	t_vec	hit_dir;
	t_vec2	point;

	center_to_hitpoint = sub(*hitpoint, cylinder->center);
	if (dot(center_to_hitpoint, cylinder->dir) < 0)
		hit_dir = sub(center_to_hitpoint, scale(cylinder->dir, cylinder->height / -2));
	else
		hit_dir = sub(center_to_hitpoint, scale(cylinder->dir, cylinder->height / 2));
	point.x = get_angle(&hit_dir, &(cylinder->system.x)) / 180;
	point.y = 1 - (vec_len(hit_dir)) / cylinder->radius;
	if (keep_ratio)
		point.y /= cylinder->circumference / cylinder->radius / 2;
	return (point);
}

t_vec2	cylinder_surface_pattern(t_cylinder *cylinder, t_hit_info *hit, int keep_ratio)
{
	t_vec2	point;
	float	height_from_base;
	t_vec	base_center_to_hit;

	point.x = get_angle(&(hit->normal), &(cylinder->system.x)) / 180;
	base_center_to_hit = sub(hit->hit_point, cylinder->covers[0].plane.point);
	height_from_base = dot(base_center_to_hit, cylinder->dir);
	point.y = height_from_base / cylinder->height;
	if (keep_ratio)
		point.y *= 2 / (cylinder->circumference / cylinder->height);
	return (point);
}

t_vec2	cylinder_texture_coordinates(t_hit_info *hit, int keep_ratio)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)(hit->obj.shape);
	if (hit->is_surface_hit)
		return (cylinder_cover_pattern(cylinder, &(hit->hit_point), keep_ratio));
	return (cylinder_surface_pattern(cylinder, hit, keep_ratio));
}

int	cut_cylinder(t_ray *ray, t_cylinder *cylinder, double *t)
{
	t_vec	hit_point;
	t_vec	projected;

	hit_point = get_ray_point(*ray, *t);
	projected = project(sub(hit_point, cylinder->center), cylinder->dir);
	if (vec_len(projected) <= cylinder->height / 2)
		return (1);
	*t = -1.0;
	return (0);
}

int	intersect_cylinder_covers(t_ray *ray, t_cylinder *cylinder, double *t)
{
	double		t_1;
	double		t_2;

	intersect_circle(ray, (void *)&(cylinder->covers[0]), &t_1, NULL);
	intersect_circle(ray, (void *)&(cylinder->covers[1]), &t_2, NULL);
	*t = get_closest_intersection(t_1, t_2);
	return (*t > 0.0);
}

int	intersect_cylinder(t_ray *ray, void *shape, double *t, int *is_surface_hit)
{
	t_quadratic	f;
	double		t_1;
	double		t_2;
	t_cylinder	*cylinder;
	double		t_cover;

    cylinder = (t_cylinder *)shape;

	double		dot_ray_dir_cylinder_dir;
	double		dot_w_cylinder_dir;
	t_vec		w;
	w = sub(ray->origin, cylinder->center);
	dot_ray_dir_cylinder_dir = dot(ray->dir, cylinder->dir);
	dot_w_cylinder_dir = dot(w, cylinder->dir);

	f.a = 1 - pow(dot_ray_dir_cylinder_dir, 2);
	f.b = 2 * (dot(ray->dir, w) - dot_ray_dir_cylinder_dir * dot_w_cylinder_dir);
	f.c = dot(w, w) - pow(dot_w_cylinder_dir, 2) - pow(cylinder->radius, 2);

	if (!solve_quadratic(f, &t_1, &t_2))
		return (0);

	*t = get_closest_intersection(t_1, t_2);
	if (*t <= 0.0)
		return (0);

	cut_cylinder(ray, cylinder, &(*t));
	intersect_cylinder_covers(ray, cylinder, &t_cover);
	*t = get_closest_intersection(*t, t_cover);

	if (is_surface_hit != NULL)
		*is_surface_hit = *t == t_cover;
	return (*t > 0.0);
}

t_vec	cylinder_normal(t_hit_info *hit)
{
	t_cylinder	*cylinder;
	t_vec		projected;
	t_vec		projected_hit_dir;
	t_vec		center_to_hitpoint;

	cylinder = (t_cylinder *)(hit->obj.shape);

	if (hit->is_surface_hit)
		return (cylinder->dir);

	center_to_hitpoint = sub(hit->hit_point, cylinder->center);
	projected = project(center_to_hitpoint, cylinder->dir);
	projected_hit_dir = sub(center_to_hitpoint, projected);
	return (normalize(projected_hit_dir));
}

int	create_cylinder(t_material *obj, t_info *info)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (1);
	cylinder->center = info->center;
	cylinder->radius = info->radius;
	cylinder->height = info->height;
	cylinder->dir = normalize(info->dir);
	cylinder->system = create_system(info->dir);
	cylinder->covers[0].radius = cylinder->radius;
	cylinder->covers[0].plane.normal = cylinder->dir;
	cylinder->covers[0].plane.point = add(info->center, scale(cylinder->dir, info->height / 2));
	cylinder->covers[1].radius = cylinder->radius;
	cylinder->covers[1].plane.normal = scale(cylinder->dir, -1);
	cylinder->covers[1].plane.point = add(info->center, scale(cylinder->dir, info->height / -2));
	cylinder->circumference = 2 * M_PI * info->radius;

	obj->shape = (void *)cylinder;
	obj->intersect = intersect_cylinder;
	obj->normal = cylinder_normal;
	obj->texture_coordinates = cylinder_texture_coordinates;
	if (info->bump_mapping)
		obj->texture = BUMP_MAP;
	if (info->procedural_texturing)
		obj->texture = CHECKERS;
	return (0);
}