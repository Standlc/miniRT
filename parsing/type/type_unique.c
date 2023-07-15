#include "minirt.h"

int check_ambuant(char **row)
{
	int	i;

	i = 1;
	while (row[i])
	{
		if (i == 1)
			if (!range_zero_one(row[1]))
				return (error_information("A\n"), 0);
		if (i == 2)
			if (!rgb_information(row[2]))
				return (error_information("A\n"), 0);
        if (i == 3)
            return (error_information("A\n"), 0);
		i++;
	}
	return (1);
}

int check_camera(char **row)
{
	int	i;

	i = 1;
	while (row[i])
	{
		if (i == 1)
			if (!vector_coordinates(row[1]))
				return (error_information("C\n"), 0);
		if (i == 2)
			if (!vector_normal_information(row[2]))
				return (error_information("C\n"), 0);
        if (i == 3)
			if (!fov_information(row[3]))
				return (error_information("C\n"), 0);
        if (i == 4)
            return (error_information("C\n"), 0);
		i++;
	}
	return (1);
}