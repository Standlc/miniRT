/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:29 by stde-la-          #+#    #+#             */
/*   Updated: 2023/09/11 12:51:59 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	cut_cylinder(t_ray *ray, t_cylinder *cylinder, double *t)
{
	t_vec	hit_to_center;

	hit_to_center = sub(get_ray_point(*ray, *t), cylinder->center);
	if (fabs(dot(&hit_to_center, &(cylinder->dir))) <= cylinder->height / 2)
		return (1);
	*t = 0.0;
	return (0);
}

int	intersect_cylinder_covers(t_ray *ray, t_cylinder *cylinder, double *t,
	t_quadratic *f)
{
	double	t_1;
	double	t_2;

	intersect_plane(ray, (void *)&(cylinder->covers[0].plane), &t_1, NULL);
	intersect_plane(ray, (void *)&(cylinder->covers[1].plane), &t_2, NULL);
	*t = get_closest_intersection(t_1, t_2);
	return (*t > 0.0 && ((*t > f->t_1 && *t < f->t_2)
			|| (*t < f->t_1 && *t > f->t_2)));
}

int	intersect_cylinder_tube(t_ray *ray, t_cylinder *cylinder, t_quadratic *f)
{
	t_vec	w;
	double	dot_ray_dir_cyl_dir;
	double	dot_w_cylinder_dir;

	w = sub(ray->origin, cylinder->center);
	dot_ray_dir_cyl_dir = dot(&(ray->dir), &(cylinder->dir));
	dot_w_cylinder_dir = dot(&w, &(cylinder->dir));
	f->a = 1 - pow2(dot_ray_dir_cyl_dir);
	f->b = 2 * (dot(&(ray->dir), &w)
			- dot_ray_dir_cyl_dir * dot_w_cylinder_dir);
	f->c = dot(&w, &w) - pow2(dot_w_cylinder_dir) - pow2(cylinder->radius);
	return (solve_quadratic(f));
}

int	intersect_cylinder(t_ray *ray, void *shape, double *t, int *is_surface_hit)
{
	t_quadratic	f;
	t_cylinder	*cylinder;
	double		t_cover;

	cylinder = (t_cylinder *)shape;
	if (!intersect_cylinder_tube(ray, cylinder, &f))
		return (0);
	*t = get_closest_intersection(f.t_1, f.t_2);
	if (*t <= 0.0)
		return (0);
	cut_cylinder(ray, cylinder, t);
	if (intersect_cylinder_covers(ray, cylinder, &t_cover, &f))
		*t = get_closest_intersection(t_cover, *t);
	if (is_surface_hit != NULL)
		*is_surface_hit = *t != t_cover;
	return (*t > 0.0);
}
