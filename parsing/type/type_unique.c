/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_unique.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:18:15 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/13 19:15:26 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_ambuant(char **row)
{
	int	i;

	i = 1;
	while (row[i])
	{
		if (i == 1 && !range_zero_one(row[1]))
			return (print_syntaxe_error("Ambient [1]", INTENSITY, "0.3"));
		if (i == 2 && !rgb_information(row[2]))
			return (print_syntaxe_error("Ambient [2]", COLOR, "200,0,255"));
		if (i == 3)
			if (!stars_option(row[3]))
				return (print_syntaxe_error("Ambient [3]", ST_ERR, "st"), 0);
		if (i == 4)
			return (error_information("Ambient light has only 3 parameters\n"),
				0);
		i++;
	}
	if (i < 3)
		return (error_information("Ambient light must have 2 parameters\n"), 0);
	return (1);
}

int	check_camera(char **row)
{
	int	i;

	i = 1;
	while (row[i])
	{
		if (i == 1 && !vector_coordinates(row[1]))
			return (print_syntaxe_error("CAMERA [1]", SPACE_POINT, "3,4,4"));
		if (i == 2 && !vector_normal_information(row[2]))
			return (print_syntaxe_error("CAMERA [2]", DIR_VECTOR, "-0.2,1,0"));
		if (i == 3 && !fov_information(row[3]))
			return (print_syntaxe_error("CAMERA [3]", FOV_ERR, "90"));
		if (i == 4)
			return (error_information("Camera has only 3 parameters\n"), 0);
		i++;
	}
	if (i != 4)
		return (error_information("Camera must have 3 parameters\n"), 0);
	return (1);
}
