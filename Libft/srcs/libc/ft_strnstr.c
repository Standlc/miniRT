/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:39:45 by svan-de-          #+#    #+#             */
/*   Updated: 2022/11/16 20:06:23 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strncmp2(const char *s1, const char *s2, unsigned int n,
size_t len)
{
	unsigned int	i;
	int				vc;

	i = 0;
	vc = 0;
	while (s2[i] != '\0' && vc == 0 && i < n && i < len)
	{
		vc = s1[i] - s2[i];
		i++;
	}
	if (vc < 0)
		return (-1);
	if (vc > 0)
		return (1);
	if (i < n)
		return (-1);
	return (0);
}

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t				i;
	unsigned int		size_find;
	int					stock;

	size_find = 0;
	i = 0;
	if (!s1)
		return (NULL);
	if (s2[0] == '\0')
		return ((char *)s1);
	while (s2[size_find] != '\0')
		size_find ++;
	while (s1[i] != '\0' && i < len)
	{
		if (s2[0] == s1[i])
		{
			stock = ft_strncmp2(&s2[0], &s1[i], size_find, len - i);
			if (stock == 0)
				return ((char *)s1 + i);
		}
		else if (s1[i] == '\0')
			return (NULL);
		i++;
	}
	return (NULL);
}
