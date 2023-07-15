#include "minirt.h"

float	cylinder_cover_pattern(t_cylinder *cylinder, t_vec *hitpoint)
{
	t_vec	center_to_hitpoint;
	t_vec	hit_dir;
	float	u;
	float	v;

	center_to_hitpoint = sub(*hitpoint, cylinder->center);
	if (dot(center_to_hitpoint, cylinder->dir) < 0)
		hit_dir = sub(center_to_hitpoint, scale(cylinder->dir, cylinder->height / -2));
	else
		hit_dir = sub(center_to_hitpoint, scale(cylinder->dir, cylinder->height / 2));
	u = get_angle(&hit_dir, &(cylinder->system.x)) / 180;
	v = 1 - (vec_len(hit_dir)) / cylinder->radius;
	v /= cylinder->circumference / cylinder->radius / 2;
	return (uv_pattern(u, v, 10));
}

float	cylinder_surface_pattern(t_cylinder *cylinder, t_ray *normal)
{
	float	u;
	float	v;
	float	height_from_base;
	t_vec	base_center_to_hit;

	u = get_angle(&(normal->dir), &(cylinder->system.x)) / 180;
	base_center_to_hit = sub(normal->origin, cylinder->covers[0].plane.point);
	height_from_base = dot(base_center_to_hit, cylinder->dir);
	v = height_from_base / cylinder->height;
	v *= 2 / (cylinder->circumference / cylinder->height);
	return (uv_pattern(u, v, 10));
}

float	cylinder_pattern(void *shape, t_ray *normal, int surface_hit)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)shape;
	if (surface_hit)
		return (cylinder_cover_pattern(cylinder, &(normal->origin)));
	return (cylinder_surface_pattern(cylinder, normal));
}

int	create_cylinder(t_material *object, t_info *info)
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
	object->shape = (void *)cylinder;
	object->intersect = intersect_cylinder;
	object->normal = cylinder_normal;
	if (info->procedural_texturing)
		object->procedural_texturing = sphere_pattern;
	else
		object->procedural_texturing = NULL;
	return (0);
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

	intersect_cirlce(ray, (void *)&(cylinder->covers[0]), &t_1, NULL);
	intersect_cirlce(ray, (void *)&(cylinder->covers[1]), &t_2, NULL);
	*t = get_closest_intersection(t_1, t_2);
	return (*t > 0.0);
}

int	intersect_cylinder(t_ray *ray, void *shape, double *t, int *surface_hit)
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

	f.a = dot(ray->dir, ray->dir) - pow(dot_ray_dir_cylinder_dir, 2);
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

	if (surface_hit != NULL)
		*surface_hit = *t == t_cover;
	return (*t > 0.0);
}

t_vec	cylinder_normal(t_vec *ray_dir, void *shape, t_vec *hit_point, int surface_hit)
{
	t_cylinder	*cylinder;
	t_vec		normal;
	t_vec		projected;
	t_vec		projected_hit_dir;
	t_vec		center_to_hitpoint;

	cylinder = (t_cylinder *)shape;
	if (surface_hit)
	{
		// printf("f]\n");
		normal = cylinder->dir;
	}
	else
	{
		center_to_hitpoint = sub(*hit_point, cylinder->center);
		projected = project(center_to_hitpoint, cylinder->dir);
		projected_hit_dir = sub(center_to_hitpoint, projected);
		normal = normalize(projected_hit_dir);
	}

	if (dot(normal, *ray_dir) > 0)
		return (scale(normal, -1));
	return (normal);
}
