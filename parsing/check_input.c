#include "minirt.h"

int	check_type(char *str)
{
	char	**row;
	int		result;

	result = 0;
	row = ft_split(str, ' ');
	if (!row)
		return (error_malloc(), 0);
	if (!ft_strncmp(row[0], "A", 2))
	{
		result = check_ambuant(row);
		return (free_split(row), result);
	}
	free_split(row);
	return (1);
}

void	check_rows(char **rows)
{
	int	i;

	i = 0;
	while (rows[i])
	{
		if (!check_type(rows[i]))
			(free_split(rows), exit(1));
		i++;
	}
}

int	check_argument(int argc, char **argv)
{
	int	i;
	int	fd;

	i = 0;	
	if (argc != 2)
		(ft_putstr_fd("Error\nAn argument is required.\n", 2), exit(1));
	if (!argv[1] || !*argv[1])
		(ft_putstr_fd("Error\nThe file must have a .rt extension.\n", 2), exit(1));
	while (argv[1][i])
		i++;
	i -= 3;
	if (i <= 0 || ft_strncmp(&argv[1][i], ".rt", 4))
		(ft_putstr_fd("Error\nThe file must have a .rt extension.\n", 2), exit(1));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		(ft_putstr_fd("Error\nThe file cannot be access.\n", 2), exit(1));
	return (fd);
}