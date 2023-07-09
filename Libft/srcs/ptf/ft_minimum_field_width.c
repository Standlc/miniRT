/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimum_field_width.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 00:18:49 by svan-de-          #+#    #+#             */
/*   Updated: 2022/12/16 21:30:05 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strdup_pf(const char *src)
{
	int		i;
	char	*str;
	int		len;

	len = 0;
	i = 0;
	while (src[len])
		len++;
	str = malloc(len * sizeof(char) + 1);
	if (!str)
		return (NULL);
	while (src[i] != '\0')
	{
		str[i] = src[i];
		i++;
	}
	str[len] = '\0';
	return (str);
}

void	ft_print_number_of(t_index *index, t_len *len, int f)
{
	if (f == 1)
	{
		while (len->number_of > 0)
		{
			index->option += ft_putchar_pf(' ');
			len->number_of--;
		}
	}
	if (f == 0)
	{
		while (len->number_of > 0)
		{
			index->option += ft_putchar_pf('0');
			len->number_of--;
		}
	}
}

void	ft_got_len(char *str, t_index *index, t_len *len)
{
	if (index->flag == 5)
		len->len_arg = 1;
	else if (index->flag == 1)
		len->len_arg = ft_len_arg(str, index);
	else if (index->flag == 2)
		len->len_arg = ft_strlen_pf(index->str_arg);
	else if (index->flag == 3)
		len->len_arg = ft_len_hex(index->arg, index);
	else if (index->flag == 4)
		len->len_arg = ft_len_hex(index->p_arg, index);
	else
		return ;
}

void	ft_check_precision(char *str, t_index *index, t_len *len)
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
		ft_print_number_of(index, len, 1);
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
	ft_print_number_of(index, len, 1);
}

void	ft_number(char *str, t_index *index)
{
	t_len	len;

	len.number_of = 0;
	len.write = 0;
	len.len_arg = 0;
	len.number_of = ft_atoi_pf(str, index);
	if (str[index->i] == '.')
	{
		ft_check_precision(str, index, &len);
		return (ft_pre(str, index, 1), (void)len);
	}
	len.write = ft_was_option(str, index);
	ft_got_len(str, index, &len);
	if (index->flag == 4 && len.len_arg == 0)
		len.write += 3;
	len.number_of -= (len.write + len.len_arg);
	ft_print_number_of(index, &len, 1);
}
