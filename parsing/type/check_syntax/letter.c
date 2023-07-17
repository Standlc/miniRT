#include "minirt.h"

int	letters_option(char *s1, char *s2)
{
	if (!s2)
	{
		if (!ft_strncmp(s1, "d", 2) || !ft_strncmp(s1, "bm", 3))
			return (1);
		return (0);
	}
	if (ft_strncmp(s1, "d", 2) && ft_strncmp(s1, "bm", 3))
		return (0);
	if (ft_strncmp(s2, "d", 2) && ft_strncmp(s2, "bm", 3))
		return (0);
	if (!ft_strncmp(s1, s2, 3))
		return (0);
	return (1);
}