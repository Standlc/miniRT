/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:24:34 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/13 14:53:48 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_argument(int argc, char **argv)
{
	int	i;
	int	fd;

	i = 0;
	if (argc != 2)
		(ft_putstr_fd("Error\nA scene file is required\n", 2), exit(1));
	if (!argv[1] || !*argv[1])
		(ft_putstr_fd(DOTRT_ERR, 2), exit(1));
	while (argv[1][i])
		i++;
	i -= 3;
	if (i <= 0 || ft_strncmp(&argv[1][i], ".rt", 4))
		(ft_putstr_fd(DOTRT_ERR, 2), exit(1));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		(ft_putstr_fd("Error\nThe scene file cannot be accessed.\n", 2), exit(1));
	return (fd);
}
