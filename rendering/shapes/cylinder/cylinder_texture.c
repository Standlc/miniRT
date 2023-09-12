/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:31 by stde-la-          #+#    #+#             */
/*   Updated: 2023/09/11 12:51:09 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec2	cylinder_cover_point(t_cylinder *cylinder, t_vec *hitpoint)
{
	t_vec	center_to_hitpoint;
	t_vec	hit_dir;
	t_vec2	point;

	center_to_hitpoint = sub(*hitpoint, cylinder->center);
	if (dot(&center_to_hitpoint, &(cylinder->dir)) < 0)
	{
		hit_dir = sub(center_to_hitpoint,
				scale(cylinder->dir, cylinder->height / -2));
	}
	else
	{
		hit_dir = sub(center_to_hitpoint,
				scale(cylinder->dir, cylinder->height / 2));
	}
	point.x = get_angle(&hit_dir, &(cylinder->system.x)) / 180 + 1;
	point.x *= (dot(&hit_dir, &(cylinder->system.z)) <= 0) * 2 - 1;
	point.y = 1 - (vec_len(hit_dir)) / cylinder->radius;
	point.y /= cylinder->circumference / cylinder->radius / 2;
	return (point);
}

t_vec2	cylinder_surface_point(t_cylinder *cylinder, t_hit_info *hit)
{
	t_vec2	point;
	float	height_from_base;
	t_vec	base_center_to_hit;

	point.x = get_angle(&(hit->normal), &(cylinder->system.x)) / 180 + 1;
	point.x *= (dot(&(hit->normal), &(cylinder->system.z)) <= 0) * 2 - 1;
	base_center_to_hit = sub(hit->hit_point, cylinder->covers->plane.point);
	height_from_base = dot(&base_center_to_hit, &(cylinder->dir));
	point.y = height_from_base / cylinder->height;
	point.y *= 2 / (cylinder->circumference / cylinder->height);
	return (point);
}

t_vec2	cylinder_texture_coordinates(t_hit_info *hit)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)(hit->obj->shape);
	if (!hit->is_surface_hit)
		return (cylinder_cover_point(cylinder, &(hit->hit_point)));
	return (cylinder_surface_point(cylinder, hit));
}
