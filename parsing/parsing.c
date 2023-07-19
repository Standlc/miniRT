#include "minirt.h"

void parsing(int argc, char **argv, t_rt *rt)
{
	t_parsing	parsing;
	char		**rows;

	parsing.fd = check_argument(argc, argv);
	parsing.number_of_materials = 0;
	parsing.number_of_lights = 0;
	rows = get_content(parsing.fd);
	check_rows(rows, &parsing);
	rt->nb_objects = parsing.number_of_materials;
	rt->nb_lights = parsing.number_of_lights;
	fill_rt(rows, rt, parsing);
	free_split(rows);
	if (close(parsing.fd) == -1)
		(ft_putstr_fd("Error\nThe file cannot be closed.\n", 2), exit(errno));
}