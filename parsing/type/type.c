/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:18:50 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/13 19:14:11 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_light(char **row)
{
	int	i;

	i = 1;
	while (row[i])
	{
		if (i == 1 && !vector_coordinates(row[1]))
			return (print_syntaxe_error("Light [1]", SPACE_POINT, "3,4,4"));
		if (i == 2 && !range_zero_one(row[2]))
			return (print_syntaxe_error("Light [2]", INTENSITY, "0.3"));
		if (i == 3 && !rgb_information(row[3]))
			return (print_syntaxe_error("Light [3]", COLOR, "200,0,255"));
		if (i == 4 && !check_double(row[4]))
			return (print_syntaxe_error("Light [4]", DIAMETER_ERR, "3.5"));
		if (i == 5)
			return (error_information("Light has only 4 parameters\n"), 0);
		i++;
	}
	if (i < 4)
		return (error_information("Light must have 3 parameters\n"), 0);
	return (1);
}

int	check_sphere(char **row)
{
	int	i;

	i = 1;
	while (row[i])
	{
		if (i == 1 && !vector_coordinates(row[1]))
			return (print_syntaxe_error("Sphere [1]", SPACE_POINT, "3,4,4"));
		if (i == 2 && !check_double(row[2]))
			return (print_syntaxe_error("Sphere [2]", DIAMETER_ERR, "3.5"));
		if (i == 3 && !rgb_information(row[3]))
			return (print_syntaxe_error("Sphere [3]", COLOR, "200,0,255"));
		if (i == 4 && !range_zero_one(row[4]))
			return (print_syntaxe_error("Sphere [4]", SMOOTHNESS, "0.6"));
		if (i == 5 && !range_zero_one(row[5]))
			return (print_syntaxe_error("Sphere [5]", REFLECTION, "0.6"));
		if (i == 6 && !letters_option(row[6]))
			return (print_syntaxe_error("Sphere [6]", TEXTURE,
					"'bm-1' or 'ch-14'"));
		if (i == 7)
			return (error_information("Sphere has only 6 parameters\n"), 0);
		i++;
	}
	if (i < 4)
		return (error_information("Sphere must have 3 parameters\n"), 0);
	return (1);
}

int	check_plan(char **row)
{
	int	i;

	i = 1;
	while (row[i])
	{
		if (i == 1 && !vector_coordinates(row[1]))
			return (print_syntaxe_error("Plane [1]", SPACE_POINT, "3,4,4"));
		if (i == 2 && !vector_normal_information(row[2]))
			return (print_syntaxe_error("Plane [2]", DIR_VECTOR, "-0.2,1,0"));
		if (i == 3 && !rgb_information(row[3]))
			return (print_syntaxe_error("Plane [3]", COLOR, "200,0,255"));
		if (i == 4 && !range_zero_one(row[4]))
			return (print_syntaxe_error("Plane [4]", REFLECTION, "0.6"));
		if (i == 5 && !range_zero_one(row[5]))
			return (print_syntaxe_error("Plane [5]", REFLECTION, "0.6"));
		if (i == 6 && !letters_option(row[6]))
			return (print_syntaxe_error("Plane [6]", TEXTURE,
					"'bm-1' or 'ch-14'"));
		if (i == 7)
			return (error_information("Plane has only 6 parameters\n"), 0);
		i++;
	}
	if (i < 4)
		return (error_information("Plane must have 3 parameters\n"), 0);
	return (1);
}

int	check_cylinder(char **row)
{
	int	i;

	i = 1;
	while (row[i])
	{
		if (i == 1 && !vector_coordinates(row[1]))
			return (print_syntaxe_error("Cylinder [1]", SPACE_POINT, "3,4,4"));
		if (i == 2 && !vector_normal_information(row[2]))
			return (print_syntaxe_error("Cylinder [2]", DIR_VECTOR, "0.2,1,0"));
		if (i == 3 && !check_double(row[3]))
			return (print_syntaxe_error("Cylinder [3]", SIZE_ERR, "6.2"));
		if (i == 4 && !check_double(row[4]))
			return (print_syntaxe_error("Cylinder [4]", SIZE_ERR, "6.2"));
		if (i == 5 && !rgb_information(row[5]))
			return (print_syntaxe_error("Cylinder [5]", COLOR, "200,0,255"));
		if ((i < 9 && i > 5) && !cylinder_cone_optionnal(row, i, CYLINDER))
			return (0);
		if (i == 9)
			return (error_information("Cylinder has only 8 parameters\n"), 0);
		i++;
	}
	if (i < 6)
		return (error_information("Cylinder must have 5 parameters\n"), 0);
	return (1);
}

int	check_cone(char **row)
{
	int	i;

	i = 1;
	while (row[i])
	{
		if (i == 1 && !vector_coordinates(row[1]))
			return (print_syntaxe_error("Cone [1]", SPACE_POINT, "3,4,4"));
		if (i == 2 && !vector_normal_information(row[2]))
			return (print_syntaxe_error("Cone [2]", DIR_VECTOR, "-0.2,1,0"));
		if (i == 3 && !check_double(row[3]))
			return (print_syntaxe_error("Cone [3]", SIZE_ERR, "6.2"));
		if (i == 4 && !check_double(row[4]))
			return (print_syntaxe_error("Cone [4]", SIZE_ERR, "6.2"));
		if (i == 5 && !rgb_information(row[5]))
			return (print_syntaxe_error("Cone [5]", COLOR, "200,0,255"));
		if ((i < 9 && i > 5) && !cylinder_cone_optionnal(row, i, CONE))
			return (0);
		if (i == 9)
			return (error_information("Cone has only 8 parameters\n"), 0);
		i++;
	}
	if (i < 6)
		return (error_information("Cone must have 5 parameters\n"), 0);
	return (1);
}
