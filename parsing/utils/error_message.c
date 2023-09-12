/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:16:33 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/10 18:17:46 by svan-de-         ###   ########.fr       */
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

void	error_essential(void)
{
	ft_putstr_fd("Error\nThe scene file is missing a required element\n", 2);
}

void	error_allocation(void)
{
	ft_putstr_fd("Error\nThe program cannot allocate memory\n", 2);
}
