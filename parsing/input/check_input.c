#include "minirt.h"

int	result_type_syntaxe(char **row, t_parsing *parsing)
{
	if (!ft_strncmp(row[0], "A", 2))
		return (check_ambuant(row));
	if (!ft_strncmp(row[0], "C", 2))
		return (check_camera(row));
	if (!ft_strncmp(row[0], "L", 2))
		return (parsing->number_of_lights++, parsing->number_of_materials++, check_light(row));
	if (!ft_strncmp(row[0], "sp", 3))
		return (parsing->number_of_materials++, check_sphere(row));
	if (!ft_strncmp(row[0], "pl", 3))
		return (parsing->number_of_materials++, check_plan(row));
	if (!ft_strncmp(row[0], "cy", 3))
		return (parsing->number_of_materials++, check_cylinder(row));
	if (!ft_strncmp(row[0], "co", 3))
		return (parsing->number_of_materials++, check_cone(row));
	error_information(row[0]);
	ft_putstr_fd("\n", 2);
	return (0);
}

int	check_type(char *str, t_parsing *parsing)
{
	char	**row;
	int		result;

	result = 0;
	row = ft_split(str, ' ');
	if (!row)
		return (error_malloc(), 0);
	result = result_type_syntaxe(row, parsing);
	free_split(row);
	return (result);
}

int	check_essential(char **rows)
{
	int i;
	int	nb_ambient;
	int	nb_camera;
	int	nb_lights;

	i = 0;
	nb_ambient = 0;
	nb_camera = 0;
	nb_lights = 0;
	while (rows[i])
	{
		if (!ft_strncmp(rows[i], "A ", 2))
			nb_ambient++;
		if (!ft_strncmp(rows[i], "C ", 2))
			nb_camera++;
		if (!ft_strncmp(rows[i], "L ", 2))
			nb_lights++;
		i++;
	}
	if (nb_ambient != 1 || nb_camera != 1 || nb_lights < 1)
		return (error_essential(), 0);
	return (1);
}

void	check_rows(char **rows, t_parsing *parsing)
{
	int	i;

	i = 0;
	if (!check_essential(rows))
		(free_split(rows), exit(1));
	while (rows[i])
	{
		if (!check_type(rows[i], parsing))
			(free_split(rows), exit(1));
		i++;
	}
}
