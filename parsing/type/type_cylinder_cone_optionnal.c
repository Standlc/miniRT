/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_cylinder_cone_optionnal.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:27:59 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/13 19:14:34 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	cylinder_cone_optionnal(char **row, int i, int type)
{
	if (type == CYLINDER)
	{
		if (i == 6 && !range_zero_one(row[6]))
			return (print_syntaxe_error("Cylinder [6]", REFLECTION, "0.6"));
		if (i == 7 && !range_zero_one(row[7]))
			return (print_syntaxe_error("Cylinder [7]", REFLECTION, "0.6"));
		if (i == 8 && !letters_option(row[8]))
			return (print_syntaxe_error("Cylinder [8]", TEXTURE,
					"'bm-1' or 'ch-14'"));
	}
	if (type == CONE)
	{
		if (i == 6 && !range_zero_one(row[6]))
			return (print_syntaxe_error("Cone [6]", REFLECTION, "0.6"));
		if (i == 7 && !range_zero_one(row[7]))
			return (print_syntaxe_error("Cone [7]", REFLECTION, "0.6"));
		if (i == 8 && !letters_option(row[8]))
			return (print_syntaxe_error("Cone [8]", TEXTURE,
					"'bm-1' or 'ch-14'"));
	}
	return (1);
}
