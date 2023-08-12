#include "minirt.h"

int	number_texture_bump_map(char *str)
{
	if (ft_strlen(str) != 1)
		return (0);
	if (!(str[0] >= '1' && str[0] <= '5'))
		return (0);
	return (1);
}

int	number_texture_checker(char *str)
{
	int	number;
	int	len;

	len = ft_strlen(str);
	if (len != 1 && len != 2)
		return (0);
	if (!(str[0] >= '1' && str[0] <= '9'))
		return (0);
	number = ft_atoi(str);
	if (!(number >= 1 && number <= 20))
		return (0);
	return (1);
}

int	letters_option(char *str)
{
	if (!ft_strncmp(str, "ch-", 3))
	{
		if (!number_texture_checker(str + 3))
			return (0);
		return (1);
	}
	if (!ft_strncmp(str, "bm-", 3))
	{
		if (!number_texture_bump_map(str + 3))
			return (0);
		return (1);
	}
	return (0);
}