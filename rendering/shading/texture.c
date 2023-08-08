#include "minirt.h"

float	checkers(t_vec2 point, float scale)
{
	float	pattern;

	pattern = (cosf(point.x * 2 * M_PI * scale) * sinf(point.y * 2 * M_PI * scale) + 1.f) / 2.f;
	return (roundf(pattern));
}

void	set_coordinate_system(t_system *system, t_vec *z)
{
	system->origin = (t_vec){0, 0, 0};
	system->z = *z;
	if (fabs(dot(&(t_vec){0, 1, 0}, &(system->z))) < 1.f)
		system->x = cross_product(&(t_vec){0, 1, 0}, &(system->z));
	else
		system->x = cross_product(&(system->z), &(t_vec){0, 0, 1});
	system->y = cross_product(&(system->z), &(system->x));
}

t_vec	bump_mapping(t_hit_info *hit)
{
	t_vec2		point;
	t_system	point_system;

	point = hit->obj->texture_coordinates(hit);
	point.y = (int)roundf(fabs(point.y) * ((hit->obj->normal_map->height * 4) - 1)) % hit->obj->normal_map->height;
	point.x = (int)roundf(fabs(point.x) * ((hit->obj->normal_map->width * 4) - 1)) % hit->obj->normal_map->width;

	set_coordinate_system(&point_system, &(hit->normal));

	hit->bump_normal = hit->obj->normal_map->map[(int)(point.y * hit->obj->normal_map->width + point.x)];
	hit->bump_normal = normalize(system_transform(&(hit->bump_normal), &(point_system)));
	if (dot(&(hit->bump_normal), &(hit->normal)) < 0)
		hit->bump_normal = scale(hit->bump_normal, -1);
	return (hit->bump_normal);
}