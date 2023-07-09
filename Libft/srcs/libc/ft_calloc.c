/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:13:36 by svan-de-          #+#    #+#             */
/*   Updated: 2022/11/17 15:26:01 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*resultat;
	size_t	size_max;

	if (!nmemb || !size)
		return (ft_calloc(1, 1));
	size_max = -1;
	if (nmemb > size_max / size)
		return (NULL);
	resultat = malloc(nmemb * size);
	if (!resultat)
		return (NULL);
	ft_bzero(resultat, nmemb * size);
	return (resultat);
}
