#include "minirt.h"

void	error_malloc()
{
	ft_putstr_fd("Error\nThe program cannot allocate memory or the file is empty\n", 2);
}

void	error_information(char *str)
{
	ft_putstr_fd("Error\nThe file contain a bad information or syntaxe : ", 2);
    ft_putstr_fd(str, 2);
}

void	error_essential()
{
	ft_putstr_fd("Error\nthe file must contain once each essential information\n", 2);
}
