/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 05:35:21 by svan-de-          #+#    #+#             */
/*   Updated: 2022/12/16 21:44:58 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_next_char(char *str, t_index *index)
{
	if (str[index->i] == 'c')
		return (index->option += ft_putchar_pf(index->arg), 0);
	else if (str[index->i] == 's' && index->flag2 != 2)
		return (index->option += ft_putstr_pf(index->str_arg), 0);
	else if (str[index->i] == 'p')
		return (index->option += ft_address(index->p_arg), 0);
	else if ((str[index->i] == 'd'
			|| str[index->i] == 'i') && index->flag2 != 3)
		return (ft_putnbr_pf(index->arg, index), 0);
	else if (str[index->i] == 'u' && index->flag2 != 3)
		return (ft_putnbr_u(index->arg, index), 0);
	else if (str[index->i] == 'x' || str[index->i] == 'X')
		return (ft_for_hex(str, str[index->i], index), 0);
	else if (str[index->i] == '%')
		return (index->option += ft_putchar_pf('%'), 0);
	else
		return (0);
}

int	ft_check_flags(char *str, t_index *index)
{
	if (str[index->i] == '#')
		return (ft_sharp(str, index), 1);
	if (str[index->i] == '+')
		return (ft_plus_space(str, index, 1), 1);
	if (str[index->i] == ' ')
		return (ft_plus_space(str, index, 2), 1);
	if (str[index->i] > '0' && str[index->i] <= '9')
		return (ft_number(str, index), 1);
	if (str[index->i] == '0')
		return (ft_zero(str, index), 1);
	if (str[index->i] == '-')
		return (ft_minus(str, index), 1);
	if (str[index->i] == '.')
		return (ft_precision(str, index), 1);
	if (ft_is_printf_char(str[index->i]))
		return (ft_next_char(str, index), 0);
	return (0);
}

int	ft_next_arg(char *str, va_list args, t_index *index)
{
	char	c;

	c = ft_what_arg(&str[index->i]);
	if (c == '%')
		return (2);
	else if (c == 'c')
		return (index->flag = 5, index->arg = va_arg(args, unsigned int), 0);
	else if (c == 'p')
		return (index->flag = 4, index->p_arg = va_arg(args, size_t), 0);
	else if (c == 's')
		return (index->flag = 2, index->str_arg = va_arg(args, char *), 0);
	else if (c == 'd' || c == 'i')
		return (index->flag = 1, index->arg = va_arg(args, int), 0);
	else if (c == 'u')
		return (index->flag = 1, index->arg = va_arg(args, unsigned int), 0);
	else if (c == 'x' || c == 'X')
		return (index->flag = 3, index->arg = va_arg(args, unsigned int), 0);
	else
		return (0);
}

void	ft_symbol(char *str, va_list args, t_index *index)
{
	if (str[index->i] == '%')
	{
		ft_set_flag(index);
		index->i++;
		if (ft_next_arg(str, args, index) == 2)
			return (ft_is_percent(str, index));
		while (ft_check_flags(str, index))
			ft_check_flag2(str, index);
		while (index->len > 0)
		{
			index->option += ft_putchar_pf(' ');
			index->len--;
		}
		index->i++;
	}
	else
		index->option += ft_putchar_pf(str[index->i++]);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	t_index	index;
	char	*str_malloc;

	if (!str)
		return (-1);
	str_malloc = ft_strdup_pf(str);
	if (!str_malloc)
		return (-1);
	index.i = 0;
	index.option = 0;
	index.arg = 1;
	index.flag = 0;
	index.p_arg = 0;
	index.len = 0;
	index.flag2 = 0;
	va_start(args, str);
	while (str[index.i])
		ft_symbol(str_malloc, args, &index);
	va_end(args);
	free(str_malloc);
	return (index.option);
}
