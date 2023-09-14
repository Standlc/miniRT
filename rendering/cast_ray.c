/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:45:51 by stde-la-          #+#    #+#             */
/*   Updated: 2023/09/11 12:35:02 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	reset_rendering(t_rt *rt)
{
	rt->rendering_frame = 1;
	ft_memset(rt->pixel_buff, 0, HEIGHT * WIDTH * sizeof(t_rgb));
	ft_memset(rt->img.img_addr, 0, HEIGHT * WIDTH * (rt->img.bpp / 8));
}

double	get_closest_intersection(double t1, double t2)
{
	if (t1 <= 0.0 && t2 <= 0.0)
		return (0.0);
	if (t1 <= 0.0)
		return (t2);
	if (t2 <= 0.0)
		return (t1);
	if (t1 < t2)
		return (t1);
	return (t2);
}

int	intersect_objects(t_world *world, t_ray *ray, t_hit_info *hit)
{
	t_material	*objects;
	double		t;
	int			is_surface_hit;
	int			i;

	objects = world->objects;
	hit->t = INFINITY;
	is_surface_hit = 0;
	i = 0;
	while (i < world->nb_objects)
	{
		if (objects[i].intersect(ray, objects[i].shape, &t, &is_surface_hit)
			&& t < hit->t)
		{
			hit->t = t;
			hit->is_surface_hit = is_surface_hit;
			hit->obj = objects + i;
		}
		i++;
	}
	return (hit->t != INFINITY);
}

int	deterministic_stars(t_vec dir)
{
	int	sum;

	sum = roundf(dir.x * 449) * roundf(dir.y * 756) + roundf(dir.z * 633);
	if (sum % 2000 == 0)
		return (1);
	return (0);
}

t_rgb	cast_ray(t_world *world, t_ray *ray, int is_specular_ray, int depth)
{
	t_hit_info	hit;

	if (depth > MAX_DEPTH + (is_specular_ray * MAX_DEPTH))
		return ((t_rgb){0.f, 0.f, 0.f});
	if (intersect_objects(world, ray, &hit))
	{
		if (hit.obj->light_intensity && world->ambient < 1.0)
			return (color_fade(hit.obj->color,
					hit.obj->light_intensity * (1 - world->ambient)));
		hit.is_specular = is_specular_ray;
		return (shade_hitpoint(world, &hit, ray, depth));
	}
	if (world->display_stars && deterministic_stars(ray->dir))
		return ((t_rgb){1.f, 1.f, 1.f});
	if (world->ambient)
		return (ambient_light(&(world->ambient_light), ray, world->ambient));
	return ((t_rgb){0.f, 0.f, 0.f});
}
