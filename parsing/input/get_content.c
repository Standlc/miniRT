/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:25:06 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/13 14:50:05 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;
	size_t	nb;

	i = -1;
	j = 0;
	nb = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * nb + 1);
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free(s1);
	free(s2);
	return (str);
}

char	check_last_char(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (i == 0)
		return ('\0');
	if (str[i - 1] != '\n')
		return ('\0');
	return ('\n');
}

void	delete_comment(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '#')
		{
			str[i] = '\n';
			str[i + 1] = '\0';
			break ;
		}
	}
}

char	*get_string(int fd)
{
	char	*tmp;
	char	*str;

	tmp = malloc(1);
	if (!tmp)
		return (NULL);
	*tmp = '\0';
	while (1)
	{
		str = get_next_line(fd);
		if (!str && *tmp)
			return (tmp);
		if (!str && !*tmp)
			return (free(tmp), NULL);
		delete_comment(str);
		str = ft_strjoin_free(tmp, str);
		if (!str)
			return (NULL);
		if (check_last_char(str) == '\0')
			return (str);
		tmp = str;
	}
}

char	**get_content(int fd)
{
	char	**rows;
	char	*str;

	str = get_string(fd);
	if (!str)
		(error_malloc(), close(fd), exit(1));
	close(fd);
	rows = ft_split(str, '\n');
	if (!rows)
		(free(str), error_malloc(), exit(1));
	free(str);
	return (rows);
}
