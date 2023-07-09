/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:23:43 by svan-de-          #+#    #+#             */
/*   Updated: 2022/12/11 21:30:45 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_pf(long nb, t_index *index)
{
	if (nb < 0)
	{
		index->option += ft_putchar_pf('-');
		nb *= -1;
	}
	if (nb > 9)
	{
		ft_putnbr_pf(nb / 10, index);
		ft_putnbr_pf(nb % 10, index);
	}
	else
		index->option += ft_putchar_pf(nb + '0');
}

void	ft_putnbr_u(unsigned int nb, t_index *index)
{
	if (nb > 9)
	{
		ft_putnbr_u(nb / 10, index);
		ft_putnbr_u(nb % 10, index);
	}
	else
		index->option += ft_putchar_pf(nb + '0');
}

int	ft_atoi_pf(char *str, t_index *index)
{
	int	resultat;

	resultat = 0;
	while (str[index->i] >= '0' && str[index->i] <= '9')
	{
		resultat = resultat * 10 + (str[index->i] - '0');
		index->i++;
	}
	return (resultat);
}

int	ft_is_sharp(t_index *index, char *str, char c)
{
	int	j;

	j = index->i;
	while (str[j] != '%')
	{
		if (str[j] == '#' && c == '#' && str[index->i - 1] == '#')
			return (1);
		if (str[j] == '#' && c == '#'
			&& (str[j + 1] > '0' && str[j + 1] <= '9'))
			return (-1);
		if (str[j] == '#' && c == '0')
			return (1);
		if (str[j] == '-' && (c == '-' || c == '1'))
		{
			if (str[j + 1] > '0' && str[j + 1] <= '9' && c == '1')
				return (index->option += ft_putchar_pf(' '), 1);
			else
				return (1);
		}
		j--;
	}
	return (0);
}

void	ft_set_flag(t_index *index)
{
	index->flag = 0;
	index->len = 0;
	index->flag2 = 0;
	index->p_arg = 0;
	index->arg = 0;
}
