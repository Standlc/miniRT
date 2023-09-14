/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:27:06 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/13 16:43:28 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_fill_rt(t_rt *rt, char **rows)
{
	free(rt->world.objects);
	free(rt->world.lights);
	free_maps(rt->normal_maps, NULL);
	free_split(rows);
	exit(1);
}

int	assign_object(t_rt *rt, t_info info, int material)
{
	static int	index_light = 0;
	static int	index_objects = 0;

	if (info.texture == BUMP_MAP)
		rt->world.objects[index_objects].normal_map
			= rt->normal_maps + info.texture_selection;
	else
		rt->world.objects[index_objects].normal_map = NULL;
	if (info.texture == CHECKERS)
		rt->world.objects[index_objects].checkers_scale
			= info.texture_selection;
	else
		rt->world.objects[index_objects].checkers_scale = 0;
	if (create_objects(material, rt->world.objects + index_objects, &info))
		return (0);
	complete_material(rt->world.objects + index_objects++, &info);
	if (material == LIGHT)
		rt->world.lights[index_light++] = rt->world.objects
			+ (index_objects - 1);
	return (1);
}

void	assign_info_at_the_world(char **rows, t_rt *rt)
{
	int		i;
	int		material;
	char	**row;
	t_info	info;

	i = 0;
	while (rows[i])
	{
		row = ft_split(rows[i], ' ');
		if (!row)
			free_fill_rt(rt, rows);
		set_zero(&info);
		material = fill_objects(row, rt, &info);
		if (material != AMBIENT && material != CAMERA)
			if (!assign_object(rt, info, material))
				(free_split(row), free_fill_rt(rt, rows));
		free_split(row);
		i++;
	}
}

void	fill_rt(char **rows, t_rt *rt, t_parsing parsing)
{
	rt->world.objects = malloc(sizeof(t_material)
			* parsing.number_of_materials);
	rt->world.lights = malloc(sizeof(t_material *)
			* parsing.number_of_lights);
	if (!rt->world.objects || !rt->world.lights)
		free_fill_rt(rt, rows);
	assign_info_at_the_world(rows, rt);
}
