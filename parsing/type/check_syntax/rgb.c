#include "minirt.h"

int	atoi_rgb(char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (i == 0 || i > 3)
		return (-1);
	return (result);
}

int	rgb_information(char *str)
{
	int	i;
	int	coma;
	int	number;

	i = 0;
	coma = 0;
	while (str[i] == ',' || (str[i] >= '0' && str[i] <= '9'))
		i++;
	if (i != (int)ft_strlen(str))
		return (0);
	i = 0;
	while (str[i])
	{
		number = atoi_rgb(&str[i]);
		if (number == -1 || number > 255)
			return (0);
		while (str[i] != ',' && str[i])
			i++;
		if (str[i] == ',')
			(i++, coma++);
	}
	if (coma != 2)
		return (0);
	return (1);
}