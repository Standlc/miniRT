/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:33 by stde-la-          #+#    #+#             */
/*   Updated: 2023/08/13 02:11:54 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	cylinder_normal(t_hit_info *hit)
{
	t_cylinder	*cylinder;
	t_vec		projected;
	t_vec		center_to_hitpoint;

	cylinder = (t_cylinder *)(hit->obj->shape);
	if (!hit->is_surface_hit)
		return (cylinder->dir);
	center_to_hitpoint = sub(hit->hit_point, cylinder->center);
	projected = project(center_to_hitpoint, cylinder->dir);
	return (normalize(sub(center_to_hitpoint, projected)));
}

void	set_cylinder_covers(t_cylinder *cylinder)
{
	cylinder->covers[0].radius = cylinder->radius;
	cylinder->covers[0].plane.normal = cylinder->dir;
	cylinder->covers[0].plane.point =
		add(cylinder->center, scale(cylinder->dir, cylinder->height / 2));
	cylinder->covers[1].radius = cylinder->radius;
	cylinder->covers[1].plane.normal = scale(cylinder->dir, -1);
	cylinder->covers[1].plane.point =
		add(cylinder->center, scale(cylinder->dir, cylinder->height / -2));
}

int	create_cylinder(t_material *obj, t_info *info)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (1);
	cylinder->center = info->center;
	cylinder->radius = info->radius;
	cylinder->height = info->height;
	cylinder->dir = normalize(info->dir);
	cylinder->system = create_system(info->dir);
	cylinder->circumference = 2 * M_PI * info->radius;
	set_cylinder_covers(cylinder);
	obj->shape = (void *)cylinder;
	obj->intersect = intersect_cylinder;
	obj->normal = cylinder_normal;
	obj->texture_coordinates = cylinder_texture_coordinates;
	obj->texture = info->texture;
	obj->hitpoint_offset = 1e-2;
	return (0);
}
