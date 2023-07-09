/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_what.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 03:17:35 by svan-de-          #+#    #+#             */
/*   Updated: 2022/12/12 17:16:18 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_for_hex(char *str, char c, t_index *index)
{
	if (c == 'X')
		ft_unsigned_hex(str, index->arg, 'X', index);
	else if (c == 'x')
		ft_unsigned_hex(str, index->arg, 'x', index);
	else
		return ;
}

int	ft_is_printf_char(char c)
{
	char	*charset;
	int		i;

	i = 0;
	charset = "cspdiuxX%";
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_was_option(char *str, t_index *index)
{
	int	j;

	j = index->i;
	while (str[j] != '%')
	{
		if (str[j] == '#' && index->arg == 0)
			return (0);
		else if (str[j] == '#' || (index->flag == 4))
			return (2);
		else if (str[j] == '+' || str[j] == ' ' || index->arg < 0)
			return (1);
		j--;
	}
	return (0);
}

int	ft_len_arg(char *str, t_index *index)
{
	int		i;
	long	n;

	i = 1;
	n = index->arg;
	if (index->flag == 1 && index->arg == 0 && index->flag2 != 1
		&& (str[index->i - 1] == '.'
			|| (str[index->i - 1] == '0' && str[index->i - 2] == '.')))
		return (index->flag2 = 3, 0);
	if (str[index->i - 1] == '0'
		&& !(str[index->i - 2] >= '0' && str[index->i - 2] <= '9')
		&& index->flag == 1 && str[index->i - 2] != '.')
		i--;
	if (n < 0)
		n *= -1;
	while (n / 10 != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_what_x(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == 'x')
			return (1);
		if (str[i] == 'X')
			return (2);
		i++;
	}
	return (0);
}
