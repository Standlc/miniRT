#include "minirt.h"

t_ray	sample_shadow_ray(t_material *light, t_ray *normal, double *light_distance)
{
    t_vec   light_sample_point;
	t_ray	shadow_ray;

	shadow_ray.origin = normal->origin;
	light_sample_point = light->light_sample(light->shape, normal);
	shadow_ray.dir = sub(light_sample_point, normal->origin);
	*light_distance = vec_len(shadow_ray.dir);
	shadow_ray.dir = normalize(shadow_ray.dir);
	return (shadow_ray);
}

int cast_shadow_ray(t_rt *rt, t_material *light, t_ray *shadow_ray, double light_distance)
{
	double  t;
	int     i;

	i = 0;
	while (i < rt->nb_objects)
	{
		if (light != (rt->objects + i)
			&& rt->objects[i].intersect(shadow_ray, rt->objects[i].shape, &t, NULL)
			&& t < light_distance)
			return (0);	
		i++;
	}
	return (1);
}

float	dls_intensity(t_rt *rt, t_dls *dls, t_ray *ray, t_ray *normal)
{
	float	distance_from_ray_origin;
	float	intensity;

	intensity = min(1 / dls->light_distance * dls->light_intensity * 2
				* dls->normal_shadow_dot * rt->nb_lights, dls->light_intensity)
				* (1 - rt->opt.ambient);
	if (dls->indirect_decay)
	{
		distance_from_ray_origin = vec_len(sub(normal->origin, ray->origin));
		return (intensity * min(1 / distance_from_ray_origin, 1));
	}
	return (intensity);
}

t_rgb	direct_light_sampling(t_rt *rt, t_ray *ray, t_hit_info *hit, int indirect_decay)
{
	t_ray		shadow_ray;
	t_material	*picked_light;
	t_dls		dls;

	picked_light = rt->lights[(int)roundf(randf() * (rt->nb_lights - 1))];
	shadow_ray = sample_shadow_ray(picked_light, &(hit->normal), &dls.light_distance);
	dls.normal_shadow_dot = dot(hit->normal.dir, shadow_ray.dir);

	if (dls.normal_shadow_dot <= 0 || !cast_shadow_ray(rt, picked_light, &shadow_ray, dls.light_distance))
		return ((t_rgb){0.f, 0.f, 0.f});

	dls.light_intensity = picked_light->light_intensity;
	dls.indirect_decay = indirect_decay;

	return (color_fade(picked_light->color, dls_intensity(rt, &dls, ray, &(hit->normal))));
}
