/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:58:51 by svan-de-          #+#    #+#             */
/*   Updated: 2022/11/16 21:08:54 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_compteurdemot(const char *s, char c)
{
	int	compteurdemot;
	int	i;

	i = 0;
	compteurdemot = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			compteurdemot++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (compteurdemot);
}

static void	*ft_free(char **split, int j)
{
	while (j >= 0)
	{
		free(split[j]);
		j--;
	}
	free(split);
	return (NULL);
}

static char	*ft_dup2(const char *s, char c)
{
	int			len;
	int			i;
	char		*dup;

	i = 0;
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	while (s[i] && s[i] != c)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static char	**ft_if(char **split, const char *s, char c, size_t *iandj)
{
	if (s[iandj[0]] != c)
	{
		split[iandj[1]] = ft_dup2(&s[iandj[0]], c);
		if (!split[iandj[1]])
			return (ft_free(split, iandj[1]));
		iandj[1]++;
		while (s[iandj[0]] != c && s[iandj[0]])
			iandj[0]++;
	}
	else
		iandj[0]++;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char			**split;
	int				compteurdemot;
	size_t			iandj[2];

	compteurdemot = ft_compteurdemot(s, c);
	split = malloc(sizeof(char *) * (compteurdemot + 1));
	iandj[0] = 0;
	iandj[1] = 0;
	if (!split || !s)
		return (NULL);
	while (s[iandj[0]])
	{
		split = ft_if(split, s, c, iandj);
		if (!split)
			return (NULL);
	}
	split[iandj[1]] = (NULL);
	return (split);
}
