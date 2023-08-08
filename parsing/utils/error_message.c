#include "minirt.h"

void	error_malloc()
{
	ft_putstr_fd("Error\nThe program cannot allocate memory or the file is empty\n", 2);
}

void	error_information(char *str)
{
	ft_putstr_fd("Error\nWrong scene file syntaxe: ", 2);
    ft_putstr_fd(str, 2);
}

void	error_essential()
{
	ft_putstr_fd("Error\nThe scene file is missing a required element\n", 2);
}

void    error_allocation()
{
    ft_putstr_fd("Error\nThe program cannot allocate memory\n", 2);
}