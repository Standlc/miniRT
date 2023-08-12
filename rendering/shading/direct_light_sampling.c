/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_light_sampling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:12 by stde-la-          #+#    #+#             */
/*   Updated: 2023/08/12 02:38:19 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	offset_ray_origin(t_hit_info *hit, float offset)
{
	return (add(hit->hit_point, scale(hit->normal, offset)));
}

void	set_shadow_ray(t_hit_info *hit, t_material *light, t_ray *shadow_ray,
	double *light_distance)
{
	shadow_ray->origin = offset_ray_origin(hit, hit->obj->hitpoint_offset);
	shadow_ray->dir = sub(sample_sphere(light->shape, NULL), hit->hit_point);
	*light_distance = vec_len(shadow_ray->dir);
	shadow_ray->dir = scale(shadow_ray->dir, 1 / *light_distance);
}

int	cast_shadow_ray(t_world *world, t_material *light, t_ray *shadow_ray,
	double light_distance)
{
	t_material	*objects;
	double		t;
	int			i;

	objects = world->objects;
	i = 0;
	while (i < world->nb_objects)
	{
		if (light != (objects + i) &&
			objects[i].intersect(shadow_ray, objects[i].shape, &t, NULL)
			&& t < light_distance)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

float	dls_intensity(t_world *world, t_dls *dls, t_ray *ray, t_vec *hit_point)
{
	float	distance_from_ray_origin;
	float	intensity;

	intensity = min(1 / dls->light_distance, dls->light_intensity)
				* dls->light_intensity
				* dls->normal_shadow_dot
				* world->nb_lights
				* (1 - world->ambient);
	if (!dls->indirect_decay)
		return (intensity);
	distance_from_ray_origin = vec_len(sub(*hit_point, ray->origin));
	return (intensity * min(1 / distance_from_ray_origin, 1));
}

t_rgb	direct_light_sampling(t_world *world, t_ray *ray, t_hit_info *hit,
	int indirect_decay)
{
	t_material	*picked_light;
	t_ray		shadow_ray;
	t_dls		dls;

	picked_light = world->lights[(int)roundf(randf() * (world->nb_lights - 1))];
	set_shadow_ray(hit, picked_light, &shadow_ray, &dls.light_distance);
	dls.normal_shadow_dot = dot(&(hit->bump_normal), &(shadow_ray.dir));

	if (dls.normal_shadow_dot <= 0 ||
		!cast_shadow_ray(world, picked_light, &shadow_ray, dls.light_distance))
		return ((t_rgb){0.f, 0.f, 0.f});

	dls.light_intensity = picked_light->light_intensity;
	dls.indirect_decay = indirect_decay;
	return (color_fade(picked_light->color,
		dls_intensity(world, &dls, ray, &(hit->hit_point))));
}
