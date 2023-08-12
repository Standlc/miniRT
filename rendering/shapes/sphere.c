/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:39 by stde-la-          #+#    #+#             */
/*   Updated: 2023/08/12 02:54:51 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec2	sphere_texture_coordinates(t_hit_info *hit)
{
	t_vec2	coordinates;

	coordinates.x = atan2f(hit->normal.z, hit->normal.x) / M_PI + 1;
	coordinates.y = acosf(hit->normal.y) / M_PI;
	return (coordinates);
}

int	intersect_sphere(t_ray *ray, void *shape, double *t, int *is_surface_hit)
{
	t_quadratic	f;
	t_sphere	*sphere;
	t_vec		w;

	(void)is_surface_hit;
	sphere = (t_sphere *)shape;
	w = sub(ray->origin, sphere->center);
	f.a = 1.0;
	f.b = 2 * dot(&(ray->dir), &w);
	f.c = dot(&w, &w) - pow2(sphere->radius);
	if (!solve_quadratic(&f))
		return (0);
	*t = get_closest_intersection(f.t_1, f.t_2);
	return (*t > 0.0);
}

t_vec	sample_sphere(void *shape, t_vec *normal_dir)
{
	t_sphere	*sphere;
	t_vec		sample_dir;

	(void)normal_dir;
	sphere = (t_sphere *)shape;
	sample_dir = scale(random_dir(), sphere->radius);
	return (add(sample_dir, sphere->center));
}

t_vec	sphere_normal(t_hit_info *hit)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)(hit->obj->shape);
	return (normalize(sub(hit->hit_point, sphere->center)));
}

int	create_sphere(t_material *obj, t_info *info)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (1);
	sphere->center = info->center;
	sphere->radius = info->radius;
	obj->shape = (void *)sphere;
	obj->intersect = intersect_sphere;
	obj->normal = sphere_normal;
	obj->texture_coordinates = sphere_texture_coordinates;
	obj->texture = info->texture;
	obj->hitpoint_offset = 1e-2;
	return (0);
}
