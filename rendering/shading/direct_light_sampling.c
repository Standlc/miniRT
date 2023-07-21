#include "minirt.h"

t_vec	offset_ray_origin(t_hit_info *hit)
{
    return (add(hit->hit_point, scale(hit->normal, 1e-2)));
}

t_ray	sample_shadow_ray(t_hit_info *hit, t_material *light, double *light_distance)
{
    t_vec   light_sample_point;
	t_ray	shadow_ray;

    shadow_ray.origin = offset_ray_origin(hit);
	light_sample_point = sample_sphere(light->shape, NULL);
	shadow_ray.dir = sub(light_sample_point, hit->hit_point);
	*light_distance = vec_len(shadow_ray.dir);
	shadow_ray.dir = scale(shadow_ray.dir, 1 / *light_distance);
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

float	dls_intensity(t_rt *rt, t_dls *dls, t_ray *ray, t_vec *hit_point)
{
	float	distance_from_ray_origin;
	float	intensity;

	intensity = min(1 / dls->light_distance, dls->light_intensity * 5)
				* dls->light_intensity * 5
				* dls->normal_shadow_dot
				* rt->nb_lights
				* (1 - rt->opt.ambient)
				// * dls->light_area
				;
	if (dls->indirect_decay)
	{
		distance_from_ray_origin = vec_len(sub(*hit_point, ray->origin));
		intensity *= min(1 / distance_from_ray_origin, 1);
	}
	return (intensity);
}

t_rgb	direct_light_sampling(t_rt *rt, t_ray *ray, t_hit_info *hit, int indirect_decay)
{
	t_ray		shadow_ray;
	t_material	*picked_light;
	t_dls		dls;

	picked_light = rt->lights[(int)roundf(randf() * (rt->nb_lights - 1))];
	shadow_ray = sample_shadow_ray(hit, picked_light, &dls.light_distance);
	dls.normal_shadow_dot = dot(hit->bump_normal, shadow_ray.dir);

	if (dls.normal_shadow_dot <= 0 ||
		!cast_shadow_ray(rt, picked_light, &shadow_ray, dls.light_distance))
		return ((t_rgb){0.f, 0.f, 0.f});

	dls.light_intensity = picked_light->light_intensity;
	dls.indirect_decay = indirect_decay;
	dls.light_area = 4 * M_PI * pow(((t_sphere *)(picked_light->shape))->radius, 2);
	return (color_fade(picked_light->color, dls_intensity(rt, &dls, ray, &(hit->hit_point))));
}
