/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:16:33 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/13 19:40:15 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	error_malloc(void)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("The program cannot allocate memory or the file is empty\n", 2);
}

void	error_information(char *str)
{
	ft_putstr_fd("Error\nWrong scene file syntaxe: ", 2);
	ft_putstr_fd(str, 2);
}

void	error_essential(int n)
{
	if (n == 1)
		ft_putstr_fd("Error\nThe scene file is missing a required element\n", 2);
	if (n == 2)
		ft_putstr_fd("Error\nThe scene file must only 1 required element\n", 2);
}

void	error_allocation(void)
{
	ft_putstr_fd("Error\nThe program cannot allocate memory\n", 2);
}

int	print_syntaxe_error(char *obj_type, char *msg, char *example)
{
	ft_putstr_fd("Error\n", 2);
	if (obj_type)
	{
		ft_putstr_fd(obj_type, 2);
		write(2, ": ", 2);
	}
	ft_putstr_fd(msg, 2);
	if (example)
	{
		write(2, "\nexample: ", 10);
		ft_putstr_fd(example, 2);
	}
	write(2, "\n", 1);
	return (0);
}
