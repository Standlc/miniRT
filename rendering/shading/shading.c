#include "minirt.h"

// int	points_inwards(t_hit_info *hit, t_vec *ray_dir)
// {
// 	return (hit->obj.texture == BUMP_MAP && dot(*ray_dir, hit->normal) <= 0);	
// }

t_rgb	indirect_lighting(t_rt *rt, t_hit_info *hit, int depth)
{
	t_ray	random_ray;

	random_ray.dir = cosine_hemisphere_dir(&(hit->bump_normal));
    random_ray.origin = offset_ray_origin(hit);
	return (cast_ray(rt, &random_ray, 0, depth + 1));
}

t_rgb	specular_reflection(t_rt *rt, t_hit_info *hit, t_ray *ray, int depth)
{
	t_ray	random_ray;
	t_vec	reflection_vec;

    reflection_vec = get_reflection(&(ray->dir), &(hit->bump_normal));
    if (hit->obj.smoothness == 1.f)
        random_ray.dir = reflection_vec;
    else
    {
        random_ray.dir = lerp(cosine_hemisphere_dir(&(hit->bump_normal)),
								reflection_vec, hit->obj.smoothness);
    }
    random_ray.origin = offset_ray_origin(hit);
    return (color_fade(cast_ray(rt, &random_ray, 1, depth + 1), 0.95f));
}

void	get_surface_normals(t_hit_info *hit, t_ray *ray)
{
	hit->normal = hit->obj.normal(hit);
	if (dot(hit->normal, ray->dir) > 0)
		hit->normal = scale(hit->normal, -1);

	if (hit->obj.texture == BUMP_MAP)
		bump_mapping(hit);
	else
		hit->bump_normal = hit->normal;
}

t_rgb	shade_hitpoint(t_rt *rt, t_hit_info *hit, t_ray *ray, int depth)
{
	t_rgb		color;
	t_rgb		direct_lighting;

	hit->hit_point = get_ray_point(*ray, hit->t);
	get_surface_normals(hit, ray);

	if (hit->obj.smoothness && randf() <= hit->obj.specular_prob)
		return (specular_reflection(rt, hit, ray, depth));

	if (hit->obj.texture == CHECKERS)
		hit->obj.color = color_fade(hit->obj.color, checkers(hit->obj.texture_coordinates(hit, 1), 10.f));

	// color = (t_rgb){0, 0, 0};
	color = indirect_lighting(rt, hit, depth);
	if (rt->nb_lights && rt->opt.ambient < 1.0)
	{
		direct_lighting = direct_light_sampling(rt, ray, hit, !hit->is_specular && depth > 1);
		color = color_add(color, direct_lighting);
	}
	return (color_mult(color, hit->obj.color));
}
