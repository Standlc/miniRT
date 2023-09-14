/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:16:07 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/13 18:08:14 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parsing(int argc, char **argv, t_rt *rt)
{
	t_parsing	parsing;
	char		**rows;

	parsing.fd = check_argument(argc, argv);
	parsing.number_of_materials = 0;
	parsing.number_of_lights = 0;
	rows = get_content(parsing.fd);
	check_rows(rows, &parsing);
	load_normal_maps(rt, rows);
	rt->world.nb_objects = parsing.number_of_materials;
	rt->world.nb_lights = parsing.number_of_lights;
	fill_rt(rows, rt, parsing);
	free_split(rows);
}
