/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fonctions_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 04:27:35 by svan-de-          #+#    #+#             */
/*   Updated: 2022/12/16 20:03:23 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_go_back(char *str, t_index *index)
{
	while (str[index->i] != '%')
		index->i--;
	index->i++;
}

int	ft_sharp(char *str, t_index *index)
{
	ft_first_f(str, index);
	if (str[index->i + 1] > '0' && str[index->i + 1] <= '9' && index->i++)
	{
		index->flag2 = 1;
		ft_number(str, index);
		ft_go_back(str, index);
	}
	else if (str[index->i + 1] == '-' && index->i++)
	{
		index->flag2 = 1;
		ft_minus(str, index);
		ft_go_back(str, index);
	}
	if (index->arg == 0)
		return (index->i++, 0);
	else if (ft_what_x(str, index->i) == 1)
		return (index->i++, index->option += ft_putstr_pf("0x"), 0);
	else if (ft_what_x(str, index->i) == 2)
		return (index->i++, index->option += ft_putstr_pf("0X"), 0);
	else
		return (0);
}

int	ft_plus_space(char *str, t_index *index, int f)
{
	ft_first_f(str, index);
	if (str[index->i + 1] > '0' && str[index->i + 1] <= '9' && index->i++)
	{
		index->flag2 = 1;
		ft_number(str, index);
		ft_go_back(str, index);
	}
	else if (str[index->i + 1] == '-' && index->i++)
	{
		index->flag2 = 1;
		ft_minus(str, index);
		ft_go_back(str, index);
	}
	if (index->arg >= 0 && f == 1)
		return (index->i++, index->option += ft_putchar_pf('+'), 0);
	if (index->arg >= 0 && f == 2)
		return (index->i++, index->option += ft_putchar_pf(' '), 0);
	return (index->i++, 0);
}

void	ft_zero(char *str, t_index *index)
{
	t_len	len;

	len.number_of = 0;
	len.write = 0;
	len.len_arg = 0;
	ft_first_f(str, index);
	if (ft_check_sign(index->i, str) || ft_pre(str, index, 0))
		return ;
	if (index->arg < 0)
	{
		len.write += 1;
		index->option += ft_putchar_pf('-');
		index->arg *= -1;
	}
	if ((index->flag == 1 || index->flag == 3) && index->i++)
	{
		len.write += ft_was_option(str, index);
		len.number_of = ft_atoi_pf(str, index);
		if (index->flag == 1)
			len.len_arg = ft_len_arg(str, index);
		else
			len.len_arg = ft_len_hex(index->arg, index);
		len.number_of -= (len.write + len.len_arg);
		ft_print_number_of(index, &len, 0);
	}
}

void	ft_precision(char *str, t_index *index)
{
	t_len	len;

	len.number_of = 0;
	len.write = 0;
	len.len_arg = 0;
	index->i++;
	len.number_of = ft_atoi_pf(str, index);
	if (index->arg < 0)
	{
		index->option += ft_putchar_pf('-');
		index->arg *= -1;
	}
	if (index->flag == 1)
		len.len_arg = ft_len_arg(str, index);
	else if (index->flag == 3)
		len.len_arg = ft_len_hex(index->arg, index);
	else if (index->flag == 2)
		return (ft_precision_f2(index, &len));
	len.number_of -= len.len_arg;
	ft_print_number_of(index, &len, 0);
	return ;
}
