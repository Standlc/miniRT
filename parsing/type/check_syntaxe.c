#include "minirt.h"

int	atoi_rgb(char *str)
{
	int	resultat;
	int	i;

	resultat = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		resultat = resultat * 10 + (str[i] - '0');
		i++;
	}
	if (i == 0)
		return (-1);
	return (resultat);
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

int	range_zero_one(char *str)
{
	int	i;

	i = 2;
	if (str[0] != '0' && str[0] != '1')
		return (0);
	if (str[0] == '1')
	{
		if (!ft_strncmp(str, "1.0", 4))
			return (1);
		return (0);
	}
	if (str[1] != '.')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i])
		return (0);
	return (1);
}
