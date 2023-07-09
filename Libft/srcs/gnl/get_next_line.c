/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 00:52:24 by svan-de-          #+#    #+#             */
/*   Updated: 2022/12/01 18:30:21 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*ft_strjoin_free(char *s1, char *s2, ssize_t readline)
{
	int		i;
	int		j;
	char	*str;
	size_t	nb;

	i = 0;
	j = 0;
	nb = ft_strlen(s1) + readline;
	str = malloc(sizeof(char) * nb + 1);
	if (!str)
		return (free(s1), NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (j < readline)
	{
		str[i] = s2[j++];
		i++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

static char	*ft_cutie(char *str_malloc)
{
	int		i;
	char	*cutie_str;

	i = 0;
	while (1)
	{
		if (str_malloc[i] == '\n' || str_malloc[i] == '\0')
		{
			if (str_malloc[i] == '\n')
				cutie_str = malloc(sizeof(char) * i + 2);
			else
				cutie_str = malloc(sizeof(char) * i + 1);
			if (!cutie_str)
				return (free(str_malloc), NULL);
			ft_memcpy(cutie_str, str_malloc, i + 1);
			if (str_malloc[i] == '\n')
				cutie_str[i + 1] = '\0';
			free(str_malloc);
			return (cutie_str);
		}
		i++;
	}
	return (free(str_malloc), NULL);
}

static char	*ft_get(int fd, char *str_reader)
{
	ssize_t		readline;
	char		*str_malloc;
	char		*cutie_str;

	readline = BUFFER_SIZE;
	str_malloc = malloc(ft_strlen(str_reader) + 1);
	if (!str_malloc)
		return (NULL);
	str_malloc = ft_memcpy(str_malloc, str_reader, ft_strlen(str_reader) + 1);
	while (readline == BUFFER_SIZE && !ft_isbackspace(str_reader))
	{
		readline = read(fd, str_reader, BUFFER_SIZE);
		if (readline < 0)
			return (free(str_malloc), NULL);
		str_malloc = ft_strjoin_free(str_malloc, str_reader, readline);
		if (!str_malloc)
			return (NULL);
	}
	if (readline < BUFFER_SIZE)
		str_reader[readline] = '\0';
	cutie_str = ft_cutie(str_malloc);
	if (!cutie_str)
		return (NULL);
	return (cutie_str);
}

char	*get_next_line(int fd)
{
	static char	strs[FOPEN_MAX + 1][(BUFFER_SIZE + 1) * (BUFFER_SIZE > 0)];
	char		*str;
	int			i;
	int			stop;

	stop = 0;
	if (fd > FOPEN_MAX || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_get(fd, strs[fd]);
	if (!str)
		return (NULL);
	while (stop == 0)
	{
		i = 0;
		if (strs[fd][i] == '\n' || strs[fd][i] == '\0')
			stop = 1;
		while (strs[fd][i])
		{
			strs[fd][i] = strs[fd][i + 1];
			i++;
		}
	}
	if (str && !(*str))
		return (free(str), NULL);
	return (str);
}
