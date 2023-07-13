#include "minirt.h"

float	cylinder_pattern(void *shape, t_ray *normal)
{
	t_cylinder	*cylinder;
	float		pattern;

	cylinder = (t_cylinder *)shape;
	
	return (roundf(pattern));
}

int	create_cylinder(t_material *object, float radius, float height, t_vec center, t_vec dir, int procedural_texturing)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (1);
	cylinder->center = center;
	cylinder->radius = radius;
	cylinder->height = height;
	cylinder->dir = normalize(dir);

	cylinder->covers[0].radius = cylinder->radius;
	cylinder->covers[0].plane.normal = cylinder->dir;
	cylinder->covers[0].plane.point = add(center, scale(cylinder->dir, height / 2));

	cylinder->covers[1].radius = cylinder->radius;
	cylinder->covers[1].plane.normal = scale(cylinder->dir, -1);
	cylinder->covers[1].plane.point = add(center, scale(cylinder->dir, height / -2));

	object->shape = (void *)cylinder;
	object->intersect = intersect_cylinder;
	object->normal = cylinder_normal;
	if (procedural_texturing)
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

	intersect_cirlce(ray, (void *)&(cylinder->covers[0]), &t_1);
	intersect_cirlce(ray, (void *)&(cylinder->covers[1]), &t_2);
	*t = get_closest_intersection(t_1, t_2);
	return (*t > 0.0);
}

int	intersect_cylinder(t_ray *ray, void *shape, double *t)
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

	cut_cylinder(ray, cylinder, t);
	intersect_cylinder_covers(ray, cylinder, &t_cover);
	*t = get_closest_intersection(*t, t_cover);
	return (*t > 0.0);
}

t_vec	cylinder_normal(void *shape, t_vec *ray_dir, t_vec *hit_point)
{
	t_cylinder	*cylinder;
	t_vec		normal;
	t_vec		projected;
	t_vec		projected_hit_dir;
	t_vec		hit_point_to_cylinder_center;

	cylinder = (t_cylinder *)shape;

	hit_point_to_cylinder_center = sub(*hit_point, cylinder->center);
	projected = project(hit_point_to_cylinder_center, cylinder->dir);
	projected_hit_dir = sub(hit_point_to_cylinder_center, projected);

	if (vec_len(projected_hit_dir) < cylinder->radius - ZERO)
		normal = cylinder->dir;
	else
		normal = normalize(projected_hit_dir);

	if (dot(normal, *ray_dir) > 0)
		return (scale(normal, -1));
	return (normal);
}
