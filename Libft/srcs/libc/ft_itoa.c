/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:42:39 by svan-de-          #+#    #+#             */
/*   Updated: 2022/11/16 20:00:26 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(long nb)
{
	int	len;

	len = 1;
	if (nb < 0)
	{
		len++;
		nb *= -1;
	}
	while (nb / 10 != 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		len;
	int		i;
	char	*resultat;

	nb = n;
	len = ft_len(nb);
	i = 0;
	resultat = malloc(sizeof(char) * len + 1);
	if (!resultat)
		return (NULL);
	resultat[len--] = '\0';
	if (nb < 0 && ++i)
	{
		resultat[0] = '-';
		nb *= -1;
	}
	while (nb / 10 > 0 && len > i)
	{
		resultat[len] = '0' + (nb % 10);
		len--;
		nb /= 10;
	}
	resultat[len] = '0' + (nb % 10);
	return (resultat);
}
