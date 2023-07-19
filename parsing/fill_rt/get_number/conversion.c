#include "minirt.h"

double conversion_double(char *str)
{
    double  decimal;
    double  integer;
    int     sign;
    int     i;
    int     j;

    i = 0;
    sign = 1;
    integer = 0;
    decimal = 0;
    if (str[i] == '-')
        (sign = -1, i++);
    while (str[i] >= '0' && str[i] <= '9')
        integer = integer * 10 + (str[i++] - '0');
    if (str[i] != '.')
        return (integer * sign);
    (i++, j = i);
    while (str[i] >= '0' && str[i] <= '9')
        decimal = decimal * 10 + (str[i++] - '0');
    (decimal /= pow(10, (i - j)), integer += decimal);
    return (integer * sign);
}

int	conversion_int(char *str)
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
	return (result);
}