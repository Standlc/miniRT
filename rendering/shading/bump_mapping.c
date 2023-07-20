#include "minirt.h"

void	set_coordinate_system(t_system *system, t_vec *z)
{
	system->z = *z;
	if (fabs(dot((t_vec){0, 1, 0}, system->z)) < 1)
		system->x = cross_product((t_vec){0, 1, 0}, system->z);
	else
		system->x = cross_product(system->z, (t_vec){0, 0, 1});
	system->y = cross_product(system->z, system->x);
	system->origin = (t_vec){0, 0, 0};
}

t_vec	bump_mapping(t_hit_info *hit)
{
	t_vec2		point;
	t_system	point_system;

	point = hit->obj.texture_coordinates(hit, 0);

	point.x = (int)roundf(fabs(point.x) * ((hit->obj.normal_map->height * 2) - 1)) % hit->obj.normal_map->height;
	point.y = (int)roundf(fabs(point.y) * ((hit->obj.normal_map->width * 2) - 1)) % hit->obj.normal_map->width;

	set_coordinate_system(&point_system, &(hit->normal));
	hit->bump_normal = hit->obj.normal_map->map[(int)(point.x * hit->obj.normal_map->height + point.y)];
	hit->bump_normal.x *= 10;
	hit->bump_normal.y *= 10;
	hit->bump_normal = normalize(system_transform(hit->bump_normal, point_system));

	// t_plane	*plane;
	// t_vec	center_dir;
	// float	u;
	// plane = (t_plane *)(hit->obj.shape);
	// center_dir = sub(hit->hit_point, plane->point);
	// u = vec_len(center_dir) * 5;
	// center_dir = normalize(center_dir);
	// hit->bump_normal = normalize(add(hit->normal, scale(center_dir, sinf(u / 2) * 0.5)));

	// hit->bump_normal = hit->normal;
	if (dot(hit->bump_normal, hit->normal) < 0)
		hit->bump_normal = scale(hit->bump_normal, -1);
	return (hit->bump_normal);
}