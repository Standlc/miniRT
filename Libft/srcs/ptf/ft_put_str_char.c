/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_str_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 20:54:22 by svan-de-          #+#    #+#             */
/*   Updated: 2022/12/16 20:15:50 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_pf(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr_pf(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_strlen_pf(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (6);
	while (str[i])
		i++;
	return (i);
}

char	ft_what_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'c')
			return ('c');
		else if (str[i] == 's')
			return ('s');
		else if (str[i] == 'p')
			return ('p');
		else if (str[i] == 'd' || str[i] == 'i')
			return ('d');
		else if (str[i] == 'u')
			return ('u');
		else if (str[i] == 'x')
			return ('x');
		else if (str[i] == 'X')
			return ('X');
		else if (str[i] == '%')
			return ('%');
		i++;
	}
	return (0);
}

int	ft_pre(char *str, t_index *index, int f)
{
	int	j;

	j = index->i;
	if (f == 0)
	{
		while (str[j] && str[j] != '.' && str[j] != '-'
			&& !ft_is_printf_char(str[j]))
			j++;
		if (str[j] == '.')
			return (index->i += 1, 1);
		else
			return (0);
	}
	if (f == 1)
	{
		while (str[index->i] != '.')
			index->i--;
		return (0);
	}
	return (0);
}
