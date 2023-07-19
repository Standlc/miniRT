#include "minirt.h"

int	letters_option(char *str)
{
	if (!ft_strncmp(str, "ch", 3))
		return (1);
	if (!ft_strncmp(str, "bm-1", 5))
		return (1);
	if (!ft_strncmp(str, "bm-2", 5))
		return (1);
	return (0);
}