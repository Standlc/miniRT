/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 06:13:02 by svan-de-          #+#    #+#             */
/*   Updated: 2022/12/16 21:31:59 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_sign(int j, char *str)
{
	char	tmp;

	if (str[j + 1] == '+' || str[j + 1] == ' ' || str[j + 1] == '#')
	{
		tmp = str[j + 1];
		str[j + 1] = str[j];
		str[j] = tmp;
		return (1);
	}
	return (0);
}

void	ft_precision_f2(t_index *index, t_len *len)
{
	int	i;

	i = 0;
	index->flag2 = 2;
	len->len_arg = ft_strlen_pf(index->str_arg);
	if (len->len_arg > len->number_of && index->str_arg != NULL)
		len->len_arg = len->number_of;
	else if (len->len_arg > len->number_of)
		len->len_arg = 0;
	while (len->len_arg > 0 && index->str_arg && index->str_arg[i])
	{
		index->option += ft_putchar_pf(index->str_arg[i]);
		i++;
		len->len_arg--;
	}
	if (index->str_arg == NULL && len->len_arg > 0)
		index->option += ft_putstr_pf("(null)");
}

void	ft_check_flag2(char *str, t_index *index)
{
	if (index->flag2 == 1)
	{
		while (str[index->i] == '-'
			|| (str[index->i] >= '0' && str[index->i] <= '9'))
			index->i++;
		index->flag2 = 0;
	}
	else
		return ;
}

void	ft_check_prec(char *str, t_index *index, t_len *len)
{
	int	precision;

	precision = 0;
	index->i++;
	precision += ft_atoi_pf(str, index);
	if (index->flag == 2)
	{
		len->len_arg += ft_strlen_pf(index->str_arg);
		if (len->len_arg > precision && index->str_arg != NULL)
			len->len_arg = precision;
		else if (len->len_arg > precision)
			len->len_arg = 0;
		len->number_of -= len->len_arg;
		index->len = len->number_of;
		return ;
	}
	len->write = ft_was_option(str, index);
	ft_got_len(str, index, len);
	precision -= len->len_arg;
	if (precision <= 0)
		precision = 0;
	if (index->flag == 4 && len->len_arg == 0)
		len->write += 3;
	len->number_of -= (precision + len->write + len->len_arg);
	index->len = len->number_of;
}

void	ft_minus(char *str, t_index *index)
{
	t_len	len;

	len.number_of = 0;
	len.write = 0;
	len.len_arg = 0;
	ft_first_f(str, index);
	if (ft_check_sign(index->i, str))
		return ;
	index->i++;
	len.number_of = ft_atoi_pf(str, index);
	if (str[index->i] == '.')
	{
		ft_check_prec(str, index, &len);
		return (ft_pre(str, index, 1), (void)len);
	}
	len.write = ft_was_option(str, index);
	ft_got_len(str, index, &len);
	if (index->flag == 4 && len.len_arg == 0)
		len.write += 3;
	len.number_of -= (len.write + len.len_arg);
	index->len = len.number_of;
}
