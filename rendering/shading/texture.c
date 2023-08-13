/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:16 by stde-la-          #+#    #+#             */
/*   Updated: 2023/08/13 02:10:29 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	checkers(t_vec2 point, float scale)
{
	float	pattern;

	scale = 2 * M_PI * scale;
	pattern = (cosf(point.x * scale) * sinf(point.y * scale) + 1.f) / 2.f;
	return (roundf(pattern));
}

void	set_coordinate_system(t_system *system, t_vec *z)
{
	system->origin = (t_vec){0.0, 0.0, 0.0};
	system->z = *z;
	if (fabs(dot(&(t_vec){0, 1, 0}, &(system->z))) < 1.f)
		system->x = cross_product(&(t_vec){0, 1, 0}, &(system->z));
	else
		system->x = cross_product(&(system->z), &(t_vec){0, 0, 1});
	system->y = cross_product(&(system->z), &(system->x));
}

void	bump_mapping(t_hit_info *hit)
{
	t_vec2			point;
	t_system		point_system;
	t_normal_map	*map;
	int				x;
	int				y;

	map = hit->obj->normal_map;
	point = hit->obj->texture_coordinates(hit);
	x = (int)roundf(fabsf(point.x) * ((map->width * 4) - 1)) % map->width;
	y = (int)roundf(fabsf(point.y) * ((map->height * 4) - 1)) % map->height;
	set_coordinate_system(&point_system, &(hit->normal));
	hit->bump_normal = map->map[y * map->width + x];
	hit->bump_normal
		= normalize(system_transform(&(hit->bump_normal), &(point_system)));
	if (dot(&(hit->bump_normal), &(hit->normal)) < 0)
		hit->bump_normal = scale(hit->bump_normal, -1);
}