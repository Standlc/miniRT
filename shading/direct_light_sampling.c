#include "minirt.h"

t_ray	sample_shadow_ray(t_material *light, t_ray *normal, double *d_to_l)
{
    t_vec   light_sample_point;
	t_ray	shadow_ray;

	shadow_ray.origin = normal->origin;
	light_sample_point = light->light_sample(light->shape, normal);
	shadow_ray.dir = sub(light_sample_point, normal->origin);
	*d_to_l = vec_len(shadow_ray.dir);
	shadow_ray.dir = normalize(shadow_ray.dir);
	return (shadow_ray);
}

int cast_shadow_ray(t_rt *rt, t_material *light, t_ray *shadow_ray, double distance_to_light)
{
	double  t_distance;
	int     i;

	i = 0;
	while (i < rt->nb_objects)
	{
		if (light != rt->objects + i && 
			rt->objects[i].intersect(shadow_ray, rt->objects[i].shape, &t_distance) && 
			t_distance < distance_to_light)
				return (0);
		i++;
	}
	return (1);
}

t_rgb	direct_light_sampling(t_rt *rt, t_ray *ray, t_ray *normal, int indirect_decay)
{
	t_ray		shadow_ray;
	double		distance_to_light;
	t_material	*random_light;
	float		normal_shadow_dot;
	float		final_light_intensity;
	float		distance_from_ray_origin;

	random_light = rt->lights[(int)roundf(randf() * (rt->nb_lights - 1))];
	shadow_ray = sample_shadow_ray(random_light, normal, &distance_to_light);
	normal_shadow_dot = dot(normal->dir, shadow_ray.dir);

	if (normal_shadow_dot <= 0 || !cast_shadow_ray(rt, random_light, &shadow_ray, distance_to_light))
		return ((t_rgb){0.f, 0.f, 0.f});

	final_light_intensity = 1
							/ distance_to_light
							* random_light->light_intensity * 2
							* normal_shadow_dot
							* rt->nb_lights;

	final_light_intensity = min(final_light_intensity, random_light->light_intensity);

	if (rt->opt.ambient)
		final_light_intensity *= 1 - rt->opt.ambient;

	if (indirect_decay)
	{
		distance_from_ray_origin = vec_len(sub(normal->origin, ray->origin));
		final_light_intensity *= min(1 / distance_from_ray_origin, 1);
	}
	return (color_fade(random_light->color, final_light_intensity));
}
