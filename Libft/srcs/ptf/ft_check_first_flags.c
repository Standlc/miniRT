/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_first_flags.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:33:23 by svan-de-          #+#    #+#             */
/*   Updated: 2022/12/16 20:38:39 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_first_f(char *str, t_index *index)
{
	if (str[index->i] == '+')
	{
		while (str[index->i + 1] == '+')
			index->i++;
	}
	else if (str[index->i] == ' ')
	{
		while (str[index->i + 1] == ' ')
			index->i++;
	}
	else if (str[index->i] == '-')
	{
		while (str[index->i + 1] == '-')
			index->i++;
	}
	else if (str[index->i] == '#')
	{
		while (str[index->i + 1] == '#')
			index->i++;
	}
	else if (str[index->i] == '0')
	{
		while (str[index->i + 1] == '0')
			index->i++;
	}
}

void	ft_is_percent(char *str, t_index *index)
{
	index->option += ft_putchar_pf('%');
	while (str[index->i] != '%')
		index->i++;
	index->i++;
}
