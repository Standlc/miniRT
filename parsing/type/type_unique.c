#include "minirt.h"

int check_ambuant(char **row)
{
	int	i;

	i = 1;
	while (row[i])
	{
		if (i == 1)
			if (!range_zero_one(row[1]))
				return (error_information("Ambient (1) light power must be between 0 and 1\nExample : 0.2\n"), 0);
		if (i == 2)
			if (!rgb_information(row[2]))
				return (error_information("Ambient (2) light color must be between 0 and 255 for each component\nExample : 150,150,255\n"), 0);
        if (i == 3)
            return (error_information("Ambient light has only 2 parameters\n"), 0);
		i++;
	}
	if (i != 3)
		return (error_information("Ambient light must have 2 parameters\n"), 0);
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
				return (error_information("Camera (1) must have a dot in the space\nExample : 0,3,-2.5\n"), 0);
		if (i == 2)
			if (!vector_normal_information(row[2]))
				return (error_information("Camera (2) must have a vector normalised\nExample : 0,-0,5,1\n"), 0);
        if (i == 3)
			if (!fov_information(row[3]))
				return (error_information("Camera (3) must have a field view between 0 and 180\nExample : 80\n"), 0);
        if (i == 4)
            return (error_information("Camera has only 3 parameters\n"), 0);
		i++;
	}
	if (i != 4)
		return (error_information("Camera must have 3 parameters\n"), 0);
	return (1);
}