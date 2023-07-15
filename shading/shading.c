#include "minirt.h"

t_rgb	indirect_lighting(t_rt *rt, t_ray *normal, int depth)
{
	t_ray	random_ray;
	t_rgb	lighting;

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

t_rgb	shade_hitpoint(t_rt *rt, t_hit_info *hit, t_ray *ray, int depth)
{
	t_rgb		direct_lighting;
	t_rgb		color;

	if (hit->obj.smoothness && randf() <= hit->obj.specular_prob)
		return (specular_lighting(rt, ray, &(hit->normal), hit->obj.smoothness, depth));

	color = (t_rgb){0.f, 0.f, 0.f};
	color = indirect_lighting(rt, &(hit->normal), depth);
	if (rt->nb_lights && rt->opt.ambient < 1.0)
	{
		direct_lighting = direct_light_sampling(rt, ray, hit, !hit->is_specular && depth > 1);
		color = color_add(color, direct_lighting);
	}

	if (hit->obj.procedural_texturing != NULL)
		hit->obj.color = color_fade(hit->obj.color, hit->obj.procedural_texturing(hit->obj.shape, &(hit->normal), hit->surface_hit));
	return (color_mult(color, hit->obj.color));
}
