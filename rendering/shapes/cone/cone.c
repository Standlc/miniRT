/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:24 by stde-la-          #+#    #+#             */
/*   Updated: 2023/09/11 12:53:15 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	cone_normal(t_hit_info *hit)
{
	t_cone	*cone;
	t_vec	top_to_hitpoint_dir;
	t_vec	local_x_dir;

	cone = (t_cone *)(hit->obj->shape);
	if (!hit->is_surface_hit)
		return (cone->base.plane.normal);
	top_to_hitpoint_dir = sub(hit->hit_point, cone->top);
	local_x_dir = cross_product(&top_to_hitpoint_dir, &(cone->dir));
	return (cross_product(&local_x_dir, &top_to_hitpoint_dir));
}

int	create_cone(t_material *obj, t_info *info)
{
	t_cone	*cone;

	cone = malloc(sizeof(t_cone));
	if (!cone)
		return (1);
	cone->center = info->center;
	cone->radius = info->radius;
	cone->height = info->height;
	cone->dir = normalize(info->dir);
	cone->top = add(info->center, scale(cone->dir, info->height));
	cone->base.radius = info->radius;
	cone->base.plane.normal = scale(cone->dir, -1);
	cone->base.plane.point = info->center;
	cone->system = create_system(info->dir);
	cone->circumference = 2 * M_PI * info->radius;
	obj->shape = (void *)cone;
	obj->intersect = intersect_cone;
	obj->normal = cone_normal;
	obj->texture_coordinates = cone_texture_coordinates;
	obj->texture = info->texture;
	obj->hitpoint_offset = 1e-5;
	return (0);
}
