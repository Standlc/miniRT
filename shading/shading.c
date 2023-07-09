#include "minirt.h"

t_rgb	indirect_lighting(t_rt *rt, Ray *normal, int is_specular_ray, int depth)
{
	Ray		random_ray;
	t_rgb	lighting;

	random_ray.origin = normal->origin;
	random_ray.dir = cosine_hemisphere_dir(&(normal->dir));
	lighting = cast_ray(rt, &random_ray, 0, depth + 1);
	if (!is_specular_ray && depth > 1)
		return (color_fade(lighting, 0.7f));
	return (lighting);
}

t_rgb	specular_lighting(t_rt *rt, Ray *ray, Ray *normal, float obj_smoothness, int depth)
{
	Ray		random_ray;
	t_vec	random_dir;
	t_vec	reflection_vec;
	t_rgb	lighting;

    random_ray.origin = normal->origin;
    reflection_vec = get_reflection(&(ray->dir), &(normal->dir));
    if (obj_smoothness == 1.f)
        random_ray.dir = reflection_vec;
    else
    {
        random_dir = cosine_hemisphere_dir(&(normal->dir));
        random_ray.dir = lerp(random_dir, reflection_vec, obj_smoothness);
    }
    lighting = cast_ray(rt, &random_ray, 1, depth + 1);
    return (color_fade(lighting, 0.95f));
}
