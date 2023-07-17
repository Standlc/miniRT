#include "minirt.h"

int check_light(char **row)
{
	int	i;

	i = 1;
	while (row[i])
	{
		if (i == 1)
			if (!vector_coordinates(row[1]))
				return (error_information("L\n"), 0);
		if (i == 2)
			if (!range_zero_one(row[2]))
				return (error_information("L\n"), 0);
        if (i == 3)
			if (!rgb_information(row[3]))
				return (error_information("L\n"), 0);
        if (i == 4)
            return (error_information("L\n"), 0);
		i++;
	}
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
				return (error_information("sp\n"), 0);
		if (i == 2)
			if (!check_double(row[2]))
				return (error_information("sp\n"), 0);
        if (i == 3)
			if (!rgb_information(row[3]))
				return (error_information("sp\n"), 0);
		if (i == 4)
			if (!range_zero_one(row[4]))
				return (error_information("sp\n"), 0);
		if (i == 5)
			if (!range_zero_one(row[5]))
				return (error_information("sp\n"), 0);
		if (i == 6)
			if (!letters_option(row[6], row[7]))
				return (error_information("pl\n"), 0);
        if (i == 8)
            return (error_information("pl\n"), 0);
		i++;
	}
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
				return (error_information("pl\n"), 0);
		if (i == 2)
			if (!vector_normal_information(row[2]))
				return (error_information("pl\n"), 0);
        if (i == 3)
			if (!rgb_information(row[3]))
				return (error_information("pl\n"), 0);
		if (i == 4)
			if (!range_zero_one(row[4]))
				return (error_information("pl\n"), 0);
		if (i == 5)
			if (!range_zero_one(row[5]))
				return (error_information("pl\n"), 0);
		if (i == 6)
			if (!letters_option(row[6], row[7]))
				return (error_information("pl\n"), 0);
        if (i == 8)
            return (error_information("pl\n"), 0);
		i++;
	}
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
				return (error_information("cy\n"), 0);
		if (i == 2)
			if (!vector_normal_information(row[2]))
				return (error_information("cy\n"), 0);
        if (i == 3)
			if (!check_double(row[3]))
				return (error_information("cy\n"), 0);
		if (i == 4)
			if (!check_double(row[4]))
				return (error_information("cy\n"), 0);
		if (i == 5)
			if (!rgb_information(row[5]))
				return (error_information("cy\n"), 0);
		if (i == 6)
			if (!range_zero_one(row[6]))
				return (error_information("cy\n"), 0);
		if (i == 7)
			if (!range_zero_one(row[7]))
				return (error_information("cy\n"), 0);
		if (i == 8)
			if (letters_option(row[8], row[9]))
				return (error_information("cy\n"), 0);
        if (i == 10)
            return (error_information("cy\n"), 0);
		i++;
	}
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
				return (error_information("co\n"), 0);
		if (i == 2)
			if (!vector_normal_information(row[2]))
				return (error_information("co\n"), 0);
        if (i == 3)
			if (!check_double(row[3]))
				return (error_information("co\n"), 0);
		if (i == 4)
			if (!check_double(row[4]))
				return (error_information("co\n"), 0);
		if (i == 5)
			if (!rgb_information(row[5]))
				return (error_information("co\n"), 0);
		if (i == 6)
			if (!range_zero_one(row[6]))
				return (error_information("co\n"), 0);
		if (i == 7)
			if (!range_zero_one(row[7]))
				return (error_information("co\n"), 0);
		if (i == 8)
			if (letters_option(row[8], row[9]))
				return (error_information("cy\n"), 0);
        if (i == 10)
            return (error_information("cy\n"), 0);
		i++;
	}
	return (1);
}
