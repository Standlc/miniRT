#include "minirt.h"

#define SPACE_POINT 	"must have a point in space"
#define INTENSITY		"intensity must range from 0 to 1"
#define SMOOTHNESS		"smoothness must range from 0 to 1"
#define COLOR			"rgb color components must range from 0 to 255 and be separated by comas only"
#define DIAMETER_ERR	"diameter must be positive"
#define HEIGHT_ERR		"height must be positive"
#define REFLECTION		"reflection probability must range from 0 to 1"
#define TEXTURE			"texture must be either checkers 'ch-(1-20)' or a bump map 'bm-(1-5)'"
#define DIR_VECTOR		"direction vector components must range from 0 to 1"

int check_light(char **row)
{
	int	i;

	i = 1;
	while (row[i])
	{
		if (i == 1)
			if (!vector_coordinates(row[1]))
				return (print_syntaxe_error("Light [1]", SPACE_POINT, NULL), 0);
		if (i == 2)
			if (!range_zero_one(row[2]))
				return (print_syntaxe_error("Light [2]", INTENSITY, NULL), 0);
        if (i == 3)
			if (!rgb_information(row[3]))
				return (print_syntaxe_error("Light [3]", COLOR, "200,0,255"), 0);
		if (i == 4)
			if (!check_double(row[4]))
				return (print_syntaxe_error("Light [4]", DIAMETER_ERR, NULL), 0);
        if (i == 5)
            return (error_information("Light has only 4 parameters\n"), 0);
		i++;
	}
	if (i < 4)
		return (error_information("Light must have 3 parameters\n"), 0);
	return (1);
}

int check_sphere(char **row)
{
	int	i;

	i = 1;
	while (row[i])
	{
		if (i == 1)
			if (!vector_coordinates(row[1]))
				return (print_syntaxe_error("Sphere [1]", SPACE_POINT, NULL), 0);
		if (i == 2)
			if (!check_double(row[2]))
				return (print_syntaxe_error("Sphere [2]", DIAMETER_ERR, NULL), 0);
        if (i == 3)
			if (!rgb_information(row[3]))
				return (print_syntaxe_error("Sphere [3]", COLOR, "150,150,100"), 0);
		if (i == 4)
			if (!range_zero_one(row[4]))
				return (print_syntaxe_error("Sphere [4]", SMOOTHNESS, NULL), 0);
		if (i == 5)
			if (!range_zero_one(row[5]))
				return (print_syntaxe_error("Sphere [5]", REFLECTION, NULL), 0);
		if (i == 6)
			if (!letters_option(row[6]))
				return (print_syntaxe_error("Sphere [6]", TEXTURE, "bm-1"), 0);
        if (i == 7)
            return (error_information("Sphere has only 6 parameters\n"), 0);
		i++;
	}
	if (i < 4)
		return (error_information("Sphere must have 3 parameters\n"), 0);
	return (1);
}

int check_plan(char **row)
{
	int	i;

	i = 1;
	while (row[i])
	{
		if (i == 1)
			if (!vector_coordinates(row[1]))
				return (error_information("Plane (1) must have a dot in the space\nExample : 7,-1.5,-8\n"), 0);
		if (i == 2)
			if (!vector_normal_information(row[2]))
				return (error_information("Plane (2) must have a vector normalised perpendicular\nExample : 1,1,0.5\n"), 0);
        if (i == 3)
			if (!rgb_information(row[3]))
				return (error_information("Plane (3) color must be between 0 and 255 for each component\nExample : 0,0,150\n"), 0);
		if (i == 4)
			if (!range_zero_one(row[4]))
				return (error_information("Plane (4) smoothness must be between 0 and 1 for each component\nExample : 0.8\n"), 0);
		if (i == 5)
			if (!range_zero_one(row[5]))
				return (error_information("Plane (5) reflexion probability must be between 0 and 1 for each component\nExample : 0.4\n"), 0);
		if (i == 6)
			if (!letters_option(row[6]))
				return (error_information("Plane (6) draughtboard is the letters 'ch' and bump mapping is the letters 'bm-(a number)'\nExample : bm-1\n"), 0);
        if (i == 7)
            return (error_information("Plane has only 6 parameters\n"), 0);
		i++;
	}
	if (i < 4)
		return (error_information("Plane must have 3 parameters\n"), 0);
	return (1);
}

int check_cylinder(char **row)
{
	int	i;

	i = 1;
	while (row[i])
	{
		if (i == 1)
			if (!vector_coordinates(row[1]))
				return (error_information("Cylinder (1) must have a dot in the space\nExample : 3,-1.5,-6\n"), 0);
		if (i == 2)
			if (!vector_normal_information(row[2]))
				return (error_information("Cylinder (2) must have a vector normalised perpendicular\nExample : 1,1,0.5\n"), 0);
        if (i == 3)
			if (!check_double(row[3]))
				return (error_information("Cylinder (3) must have a diameter positive\nExample : 2\n"), 0);
		if (i == 4)
			if (!check_double(row[4]))
				return (error_information("Cylinder (4) must have a height positive\nExample : 6.75\n"), 0);
		if (i == 5)
			if (!rgb_information(row[5]))
				return (error_information("Cylinder (5) color must be between 0 and 255 for each component\nExample : 0,150,100\n"), 0);
		if (i == 6)
			if (!range_zero_one(row[6]))
				return (error_information("Cylinder (6) smoothness must be between 0 and 1 for each component\nExample : 0.8\n"), 0);
		if (i == 7)
			if (!range_zero_one(row[7]))
				return (error_information("Cylinder (7) reflexion probability must be between 0 and 1 for each component\nExample : 0.4\n"), 0);
		if (i == 8)
			if (!letters_option(row[8]))
				return (error_information("Cylinder (8) draughtboard is the letters 'ch' and bump mapping is the letters 'bm-(a number)'\nExample : bm-1\n"), 0);
        if (i == 9)
            return (error_information("Cylinder has only 8 parameters\n"), 0);
		i++;
	}
	if (i < 6)
		return (error_information("Cylinder must have 5 parameters\n"), 0);
	return (1);
}

int check_cone(char **row)
{
	int	i;

	i = 1;
	while (row[i])
	{
		if (i == 1)
			if (!vector_coordinates(row[1]))
				return (error_information("Cone (1) must have a dot in the space\nExample : 3,-1.5,-6\n"), 0);
		if (i == 2)
			if (!vector_normal_information(row[2]))
				return (error_information("Cone (2) must have a vector normalised perpendicular\nExample : 1,1,0.5\n"), 0);
        if (i == 3)
			if (!check_double(row[3]))
				return (error_information("Cone (3) must have a diameter positive\nExample : 2\n"), 0);
		if (i == 4)
			if (!check_double(row[4]))
				return (error_information("Cone (4) must have a height positive\nExample : 6.75\n"), 0);
		if (i == 5)
			if (!rgb_information(row[5]))
				return (error_information("Cone (5) color must be between 0 and 255 for each component\nExample : 0,150,100\n"), 0);
		if (i == 6)
			if (!range_zero_one(row[6]))
				return (error_information("Cone (6) smoothness must be between 0 and 1 for each component\nExample : 0.8\n"), 0);
		if (i == 7)
			if (!range_zero_one(row[7]))
				return (error_information("Cone (7) reflexion probability must be between 0 and 1 for each component\nExample : 0.4\n"), 0);
		if (i == 8)
			if (!letters_option(row[8]))
				return (error_information("Cone (8) draughtboard is the letters 'ch' and bump mapping is the letters 'bm'\nExample : bm-1\n"), 0);
        if (i == 9)
            return (error_information("Cone has only 8 parameters\n"), 0);
		i++;
	}
	if (i < 6)
		return (error_information("Cone must have 5 parameters\n"), 0);
	return (1);
}
