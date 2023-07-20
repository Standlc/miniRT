#include "minirt.h"

// 350
// 736
// 512
// 1000

int	read_normal_map(t_normal_map *normal_map, char *file_name)
{
	int		i;
	char	*line;

	int	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (1);

	// A CALCULER AVANT !!!
	normal_map->height = 736;
	normal_map->width = 736;
	// A CALCULER AVANT !!!

	normal_map->map = malloc(sizeof(t_vec) * normal_map->height * normal_map->height);
	if (!normal_map->map)
		return (1);

	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		char	**rgb = ft_split(line, ' ');
		if (!rgb)
			return (1);
		normal_map->map[i].x = atoi(rgb[0]) / 255.0;
		normal_map->map[i].y = atoi(rgb[1]) / 255.0;
		normal_map->map[i].z = atoi(rgb[2]) / 255.0;

		normal_map->map[i].x = (normal_map->map[i].x * 2 - 1);
		normal_map->map[i].y = (normal_map->map[i].y * 2 - 1);
		normal_map->map[i].z = normal_map->map[i].z * 2 - 1;

		normal_map->map[i] = normalize(normal_map->map[i]);
		free(line);
		free(rgb[0]);
		free(rgb[1]);
		free(rgb[2]);
		free(rgb);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (0);
}
