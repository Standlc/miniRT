/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:20:51 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/13 15:00:38 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	atoi_rgb(char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (i == 0 || i > 3)
		return (-1);
	return (result);
}

int	good_rgb_syntaxe(char *str)
{
	int	i;
	int	coma;
	int	number;

	i = 0;
	coma = 0;
	while (str[i])
	{
		number = atoi_rgb(&str[i]);
		if (number == -1 || number > 255)
			return (0);
		while (str[i] != ',' && str[i])
			i++;
		if (str[i] == ',')
		{
			i++;
			coma++;
		}
	}
	if (coma != 2)
		return (0);
	return (1);
}

int	rgb_information(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ',' || (str[i] >= '0' && str[i] <= '9'))
		i++;
	if (i != (int)ft_strlen(str))
		return (0);
	if (!good_rgb_syntaxe(str))
		return (0);
	return (1);
}
