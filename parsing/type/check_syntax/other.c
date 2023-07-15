#include "minirt.h"

int check_for_1(char *str)
{
    if (!ft_strncmp(str, "1", 2) || !ft_strncmp(str, "1,", 2))
        return (1);
    if (!ft_strncmp(str, "1.0", 4) || !ft_strncmp(str, "1.0,", 4))
        return (1);
    return (0);
}

int check_double(char *str)
{
	int	    i;

	i = 0;
    if (!(str[0] >= '0' && str[0] <= '9'))
        return (0);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (!str[i])
        return (1);
    if (str[i] != '.')
        return (0);
    i++;
    if (!(str[i] >= '0' && str[i] <= '9'))
        return (0);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
    if (str[i])
        return (0);
	return (1);
}
