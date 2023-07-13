#include "minirt.h"

t_rgb	indirect_lighting(t_rt *rt, t_ray *normal, int depth)
{
	t_ray		random_ray;
	t_rgb	lighting;

    // if (depth >= rt->opt.max_depth)
    //     return ((t_rgb){0.f, 0.f, 0.f});
	random_ray.origin = normal->origin;
	random_ray.dir = cosine_hemisphere_dir(&(normal->dir));
	lighting = cast_ray(rt, &random_ray, 0, depth + 1);
	return (lighting);
}

t_rgb	specular_lighting(t_rt *rt, t_ray *ray, t_ray *normal, float obj_smoothness, int depth)
{
	t_ray	random_ray;
	t_vec	random_dir;
	t_vec	reflection_vec;
	t_rgb	lighting;

    // if (depth >= rt->opt.max_depth * 2)
    //     return ((t_rgb){0.f, 0.f, 0.f});
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
