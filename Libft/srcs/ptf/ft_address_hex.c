/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_address_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 22:31:03 by svan-de-          #+#    #+#             */
/*   Updated: 2022/12/21 23:42:05 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_zero(char *str, t_index *index)
{
	int	j;

	j = index->i;
	if (str[j - 1] == '.')
	{
		if (str[j - 2] >= '0' && str[j - 2] <= '9')
			return (index->option += ft_putchar_pf(' '), 1);
		else
			return (1);
	}
	if (str[j - 1] == '0' && str[j - 2] == '.')
	{
		if (str[j - 3] >= '0' && str[j - 3] <= '9')
			return (index->option += ft_putchar_pf(' '), 1);
		else
			return (1);
	}
	return (0);
}

size_t	ft_len_hex(size_t number, t_index *index)
{
	int	i;

	i = 1;
	if (number == 0 && index->flag == 4)
		return (0);
	if (number == 0)
		return (1);
	while (number / 16 > 0)
	{
		i++;
		number /= 16;
	}
	return (i);
}

void	ft_unsigned_hex(char *str, unsigned int number, char c, t_index *index)
{
	if (index->arg == 0 && ft_check_zero(str, index))
		return ;
	if (number >= 16)
	{
		ft_unsigned_hex(str, number / 16, c, index);
		ft_unsigned_hex(str, number % 16, c, index);
	}
	else
	{
		if (number <= 9)
			index->option += ft_putchar_pf(number + '0');
		else
		{
			if (c == 'X')
				index->option += ft_putchar_pf(number - 10 + 'A');
			if (c == 'x')
				index->option += ft_putchar_pf(number - 10 + 'a');
		}
	}
}

void	ft_hexadecimal(size_t number_address, int *index_option)
{
	if (number_address >= 16)
	{
		ft_hexadecimal(number_address / 16, index_option);
		ft_hexadecimal(number_address % 16, index_option);
	}
	else
	{
		if (number_address > 9)
			*index_option += ft_putchar_pf(number_address - 10 + 'a');
		else
			*index_option += ft_putchar_pf(number_address + '0');
	}
}

int	ft_address(size_t number_address)
{
	int	index_option;

	index_option = 0;
	if (number_address == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	index_option += 2;
	ft_hexadecimal(number_address, &index_option);
	return (index_option);
}
