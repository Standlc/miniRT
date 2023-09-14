/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:27:42 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/10 18:27:57 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	fill_ambient(char **row, t_rt *rt)
{
	rt->world.ambient = conversion_double(row[1]);
	get_value_rgb(row[2], &(rt->world.ambient_light));
	if (row[3] && !ft_strncmp(row[3], "st", 3))
		rt->world.display_stars = 1;
	else
		rt->world.display_stars = 0;
}

void	fill_camera(char **row, t_rt *rt)
{
	get_value_vec(row[1], &(rt->world.cam.system.origin));
	get_value_vec(row[2], &(rt->world.cam.dir));
	rt->world.cam.dir = normalize(rt->world.cam.dir);
	rt->world.cam.field_view = (double)conversion_int(row[3]);
}
