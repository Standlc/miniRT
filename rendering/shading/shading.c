/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:14 by stde-la-          #+#    #+#             */
/*   Updated: 2023/08/12 03:01:03 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	indirect_lighting(t_world *world, t_hit_info *hit, int depth)
{
	t_ray	random_ray;

	random_ray.dir = cosine_hemisphere_dir(&(hit->bump_normal));
    random_ray.origin = offset_ray_origin(hit, hit->obj->hitpoint_offset);
	return (cast_ray(world, &random_ray, 0, depth + 1));
}

t_rgb	specular_reflection(t_world *world, t_hit_info *hit, t_ray *ray,
	int depth)
{
	t_ray	random_ray;
	t_vec	reflection_vec;

    reflection_vec = get_reflection(&(ray->dir), &(hit->bump_normal));
    if (hit->obj->smoothness == 1.f)
        random_ray.dir = reflection_vec;
    else
        random_ray.dir = lerp(cosine_hemisphere_dir(&(hit->bump_normal)),
								reflection_vec, hit->obj->smoothness);
    random_ray.origin = offset_ray_origin(hit, hit->obj->hitpoint_offset);
    return (color_fade(cast_ray(world, &random_ray, 1, depth + 1), 0.95f));
}

void	set_surface_normals(t_hit_info *hit, t_ray *ray)
{
	hit->normal = hit->obj->normal(hit);
	if (dot(&(hit->normal), &(ray->dir)) > 0)
		hit->normal = scale(hit->normal, -1);

	if (hit->obj->texture == BUMP_MAP)
		bump_mapping(hit);
	else
		hit->bump_normal = hit->normal;
}

t_rgb	shade_hitpoint(t_world *world, t_hit_info *hit, t_ray *ray, int depth)
{
	t_rgb	color;

	hit->hit_point = get_ray_point(*ray, hit->t);
	set_surface_normals(hit, ray);

	if (hit->obj->smoothness && randf() <= hit->obj->specular_prob)
		return (specular_reflection(world, hit, ray, depth));

	if (hit->obj->texture == CHECKERS
		&& !checkers(hit->obj->texture_coordinates(hit), 10.f))
			return ((t_rgb){0.f, 0.f, 0.f});

	// color = (t_rgb){0, 0, 0};
	color = indirect_lighting(world, hit, depth);
	if (world->ambient < 1.f)
	{
		color = color_add(color, direct_light_sampling(world, ray, hit,
			// !hit->is_specular && depth > 1
			0
			));
	}
	return (color_mult(color, hit->obj->color));
}
