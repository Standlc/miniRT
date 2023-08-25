/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:37 by stde-la-          #+#    #+#             */
/*   Updated: 2023/08/12 02:57:14 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	plane_bump_mapping(t_hit_info *hit)
{
	t_plane	*plane;
	t_vec	center_dir;
	float	u;

	plane = (t_plane *)(hit->obj->shape);
	center_dir = sub(hit->hit_point, plane->point);
	u = vec_len(center_dir) * 5;
	center_dir = normalize(center_dir);
	hit->normal = normalize(add(hit->normal, scale(center_dir, sinf(u) * 0.5)));
	return (hit->normal);
}

t_vec2	plane_texture_coordinates(t_hit_info *hit)
{
	t_plane	*plane;
	t_vec2	point;

	plane = (t_plane *)(hit->obj->shape);
	point.x = dot(&(hit->hit_point), &(plane->system.x)) / 10;
	point.y = dot(&(hit->hit_point), &(plane->system.z)) / 10;
	return (point);
}

t_vec	plane_normal(t_hit_info *hit)
{
	t_plane	*plane;
	
	plane = (t_plane *)(hit->obj->shape);
	return (plane->normal);
}

int	intersect_plane(t_ray *ray, void *shape, double *t, int *is_surface_hit)
{
	double	d;
	double	n_ray_dot;
	t_plane	*plane;

	(void)is_surface_hit;
	plane = (t_plane *)shape;
	n_ray_dot = dot(&(plane->normal), &(ray->dir));
	if (n_ray_dot == 0.0)
	{
		*t = 0;
		return (0);
	}
	d = dot(&(plane->normal), &(plane->point));
	*t = (d - dot(&(plane->normal), &(ray->origin))) / n_ray_dot;
	return (*t > 0.0);
}

int	create_plane(t_material *obj, t_info *info)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (1);
	plane->point = info->center;
	plane->normal = normalize(info->dir);
	plane->system = create_system(plane->normal);
	obj->shape = (void *)plane;
	obj->intersect = intersect_plane;
	obj->normal = plane_normal;
	obj->texture_coordinates = plane_texture_coordinates;
	obj->texture = info->texture;
	obj->hitpoint_offset = 1e-2;
	return (0);
}

// int	intersect_triangle(t_tri triangle, t_ray ray, double *t)
// {
// 	t_vec	intersection;
// 	t_vec	edge;
// 	t_vec	v_to_intersection;

// 	if (!intersect_plane(&ray, &triangle.plane, t))
// 		return (0);
// 	intersection = get_ray_point(ray, *t);
// 	t_vec	normal = triangle.plane.normal;

// 	edge = sub(triangle.a, triangle.b);
// 	v_to_intersection = sub(intersection, triangle.b);
// 	if (dot(normal, cross_product(edge, v_to_intersection)) < 0)
// 		return (0);

// 	edge = sub(triangle.b, triangle.c);
// 	v_to_intersection = sub(intersection, triangle.c);
// 	if (dot(normal, cross_product(edge, v_to_intersection)) < 0)
// 		return (0);

// 	edge = sub(triangle.c, triangle.a);
// 	v_to_intersection = sub(intersection, triangle.a);
// 	if (dot(normal, cross_product(edge, v_to_intersection)) < 0)
// 		return (0);
// 	return (1);
// }