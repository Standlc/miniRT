#include "minirt.h"

void	print_row(char **rows)
{
	for (int i = 0; rows[i]; i++)
		printf("%s\n", rows[i]);
}

// int main(int argc, char **argv)
// {
// 	int	fd;
// 	char **rows;

// 	fd = check_argument(argc, argv);
// 	rows = get_content(fd);
// 	check_rows(rows);
// 	//print_row(rows);
// 	free_split(rows);
// }