#include "minirt.h"

void	print_syntaxe_error(char *obj_type, char *msg, char *example)
{
	ft_putstr_fd("Error\n", 2);
	if (obj_type)
	{
		ft_putstr_fd(obj_type, 2);
		write(2, ": ", 2);
	}
	ft_putstr_fd(msg, 2);
	if (example)
	{
		write(2, "\nexample: ", 10);
		ft_putstr_fd(example, 2);
	}
	write(2, "\n", 1);
}

void parsing(int argc, char **argv, t_rt *rt)
{
	t_parsing	parsing;
	char		**rows;

	parsing.fd = check_argument(argc, argv);
	parsing.number_of_materials = 0;
	parsing.number_of_lights = 0;
	rows = get_content(parsing.fd);
	if (close(parsing.fd) == -1)
		(ft_putstr_fd("Error\nThe file cannot be closed\n", 2), exit(1));
	check_rows(rows, &parsing);
	load_normal_maps(rt, rows);
	rt->world.nb_objects = parsing.number_of_materials;
	rt->world.nb_lights = parsing.number_of_lights;
	fill_rt(rows, rt, parsing);
	free_split(rows);
}