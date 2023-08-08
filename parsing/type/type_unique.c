#include "minirt.h"

int check_ambuant(char **row)
{
	int	i;

	i = 1;
	while (row[i])
	{
		if (i == 1)
			if (!range_zero_one(row[1]))
				return (print_syntaxe_error("Ambient light [1]", "intensity must be between 0 and 1", NULL), 0);
		if (i == 2)
			if (!rgb_information(row[2]))
				return (print_syntaxe_error("Ambient light [1]", "rgb color components must range from 0 to 255", "180,200,255"), 0);
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
				return (print_syntaxe_error("Camera [1]", "must have a point in space", NULL), 0);
		if (i == 2)
			if (!vector_normal_information(row[2]))
				return (print_syntaxe_error("Camera [2]", "direction vector components must range from 0 to 1", "0,0.5,1"), 0);
        if (i == 3)
			if (!fov_information(row[3]))
				return (print_syntaxe_error("Camera [3]", "field view must range from 0 to 180", NULL), 0);
        if (i == 4)
            return (error_information("Camera has only 3 parameters\n"), 0);
		i++;
	}
	if (i != 4)
		return (error_information("Camera must have 3 parameters\n"), 0);
	return (1);
}