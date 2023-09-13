/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_rt_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:08:57 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/13 15:09:13 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	complete_material(t_material *object, t_info *info)
{
	object->color = info->color;
	object->light_intensity = info->light_intensity;
	object->smoothness = info->smoothness;
	object->specular_prob = info->specular_prob;
}

int	create_objects(int material, t_material *object, t_info *info)
{
	if (material == LIGHT)
		return (create_sphere(object, info));
	if (material == SPHERE)
		return (create_sphere(object, info));
	if (material == PLAN)
		return (create_plane(object, info));
	if (material == CYLINDER)
		return (create_cylinder(object, info));
	if (material == CONE)
		return (create_cone(object, info));
	return (0);
}

int	fill_objects(char **row, t_rt *rt, t_info *info)
{
	if (!ft_strncmp(row[0], "A", 2))
		return (fill_ambient(row, rt), AMBIENT);
	if (!ft_strncmp(row[0], "C", 2))
		return (fill_camera(row, rt), CAMERA);
	if (!ft_strncmp(row[0], "L", 2))
		return (fill_light(row, info), LIGHT);
	if (!ft_strncmp(row[0], "sp", 3))
		return (fill_sphere(row, info), SPHERE);
	if (!ft_strncmp(row[0], "pl", 3))
		return (fill_plan(row, info), PLAN);
	if (!ft_strncmp(row[0], "cy", 3))
		return (fill_cylinder_cone(row, info), CYLINDER);
	if (!ft_strncmp(row[0], "co", 3))
		return (fill_cylinder_cone(row, info), CONE);
	return (0);
}

void	set_zero(t_info *info)
{
	info->color.r = 0;
	info->color.g = 0;
	info->color.b = 0;
	info->smoothness = 0;
	info->specular_prob = 0;
	info->light_intensity = 0;
	info->center.x = 0;
	info->center.y = 0;
	info->center.z = 0;
	info->dir.x = 0;
	info->dir.y = 0;
	info->dir.z = 0;
	info->radius = 0;
	info->height = 0;
	info->texture = 0;
	info->texture_selection = 0;
}
