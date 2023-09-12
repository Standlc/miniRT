/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:20:38 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/10 18:20:47 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	range_zero_one(char *str)
{
	int	i;

	i = 2;
	if (str[0] != '0' && str[0] != '1')
		return (0);
	if (str[0] == '1')
	{
		if (!ft_strncmp(str, "1.0", 4) || !ft_strncmp(str, "1", 2))
			return (1);
		return (0);
	}
	if (!ft_strncmp(str, "0", 2))
		return (1);
	if (str[1] != '.' || !str[2])
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] || i - 2 > 9)
		return (0);
	return (1);
}

int	fov_information(char *str)
{
	int	number;
	int	i;

	i = 0;
	number = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] || i > 3)
		return (0);
	if (number < 0 || number > 180)
		return (0);
	return (1);
}
