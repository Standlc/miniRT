/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:19:52 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/10 18:20:04 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_vector_null(char *str)
{
	int		i;
	int		number_of_zero;
	double	number;

	i = 0;
	number_of_zero = 0;
	while (str[i])
	{
		number = conversion_double(&str[i]);
		if (number == 0)
			number_of_zero++;
		while (str[i] != ',' && str[i])
			i++;
		if (str[i] == ',')
			i++;
	}
	if (number_of_zero == 3)
		return (0);
	return (1);
}
