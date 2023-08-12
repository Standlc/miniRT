/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:20 by stde-la-          #+#    #+#             */
/*   Updated: 2023/08/11 15:06:46 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	cut_cone_surface(t_cone *cone, t_vec hit_point, double *t)
{
	t_vec	hit_to_center;
	double	projected_height;

	if (*t <= 0.0)
		return (0);
	hit_to_center = sub(hit_point, cone->center);
	projected_height = dot(&hit_to_center, &(cone->dir));
	if (projected_height <= cone->height && projected_height > 0.0)
		return (1);
	*t = 0.0;
	return (0);
}

int	intersect_entire_cone(t_ray *ray, t_cone *cone, t_quadratic *f)
{
	t_vec	w;
	double	m;
	double	dot_ray_dir_h;
	double	dot_w_h;
	double	dot_w_h_squared;

	m = pow2(cone->radius) / pow2(cone->height);
	w = sub(ray->origin, cone->top);
	dot_ray_dir_h = dot(&(ray->dir), &(cone->dir));
	dot_w_h = dot(&w, &(cone->dir));
	dot_w_h_squared = pow2(dot_w_h);

	f->a = 1 - m * pow2(dot_ray_dir_h) - pow2(dot_ray_dir_h);
	f->b = 2 * (dot(&(ray->dir), &w) - m
		* dot_ray_dir_h * dot_w_h - dot_ray_dir_h * dot_w_h);
	f->c = dot(&w, &w) - m * dot_w_h_squared - dot_w_h_squared;
	return (solve_quadratic(f));
}

int	intersect_cone(t_ray *ray, void *shape, double *t, int *is_surface_hit)
{
	t_quadratic	f;
	t_cone		*cone;
	double		t_base;

	cone = (t_cone *)shape;
	if (!intersect_entire_cone(ray, cone, &f))
		return (0);

	if (dot(&(cone->dir), &(ray->dir)) >= 0)
	{
		*t = get_closest_intersection(f.t_1, f.t_2);
		cut_cone_surface(cone, get_ray_point(*ray, *t), t);
	}
	else
	{
		cut_cone_surface(cone, get_ray_point(*ray, f.t_1), &f.t_1);
		cut_cone_surface(cone, get_ray_point(*ray, f.t_2), &f.t_2);
		*t = get_closest_intersection(f.t_1, f.t_2);
	}

	intersect_circle(ray, (void *)&(cone->base), &t_base, NULL);
	*t = get_closest_intersection(*t, t_base);

	if (is_surface_hit != NULL)
		*is_surface_hit = *t != t_base;
	return (*t > 0.0);
}
