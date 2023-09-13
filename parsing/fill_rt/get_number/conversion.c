/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:28:52 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/13 17:00:39 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	conversion_double(char *str)
{
	double	decimal;
	double	integer;
	int		sign;
	int		i;
	int		j;

	i = 0;
	sign = 1;
	integer = 0;
	decimal = 0;
	sign = (str[i] == '-') * -2 + 1;
	i += (str[i] == '-');
	while (str[i] >= '0' && str[i] <= '9')
		integer = integer * 10 + (str[i++] - '0');
	if (str[i] != '.')
		return (integer * sign);
	i++;
	j = i;
	while (str[i] >= '0' && str[i] <= '9')
		decimal = decimal * 10 + (str[i++] - '0');
	decimal /= pow(10, (i - j));
	integer += decimal;
	return (integer * sign);
}

int	conversion_int(char *str)
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
	return (result);
}
