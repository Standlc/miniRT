/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:23 by stde-la-          #+#    #+#             */
/*   Updated: 2023/09/11 12:53:03 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec2	cone_base_point(t_cone *cone, t_vec *center_to_hitpoint)
{
	t_vec2	point;

	point.x = get_angle(center_to_hitpoint, &(cone->system.x)) / 180 + 1;
	point.x *= (dot(center_to_hitpoint, &(cone->system.z)) <= 0) * 2 - 1;
	point.y = vec_len(*center_to_hitpoint) / cone->radius;
	point.y /= cone->circumference / cone->radius / 2;
	return (point);
}

t_vec2	cone_surface_point(t_cone *cone, t_vec *center_to_hitpoint,
	t_vec *hitpoint)
{
	t_vec	projected;
	t_vec	projected_to_hitpoint;
	float	height_from_base;
	t_vec2	point;

	projected = project(*center_to_hitpoint, cone->dir);
	projected_to_hitpoint = sub(*hitpoint, add(cone->center, projected));
	point.x = get_angle(&projected_to_hitpoint, &(cone->system.x)) / 180 + 1;
	point.x *= (dot(&projected_to_hitpoint, &(cone->system.z)) <= 0) * 2 - 1;
	height_from_base = dot(center_to_hitpoint, &(cone->dir));
	point.y = (height_from_base / cone->height);
	point.y *= 2 / (cone->circumference / cone->height);
	return (point);
}

t_vec2	cone_texture_coordinates(t_hit_info *hit)
{
	t_cone	*cone;
	t_vec	center_to_hitpoint;

	cone = (t_cone *)(hit->obj->shape);
	center_to_hitpoint = sub(hit->hit_point, cone->center);
	if (!hit->is_surface_hit)
		return (cone_base_point(cone, &center_to_hitpoint));
	return (cone_surface_point(cone, &center_to_hitpoint, &(hit->hit_point)));
}
