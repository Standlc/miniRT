#include "minirt.h"

int	get_rgb_pixel_value(int fd, t_vec *map)
{
	char	*str;
	char	**rgb;
	int		i;

	str = get_next_line(fd);
	if (!str)
		return (error_malloc(), 0);
	i = 0;
	while (str != NULL && *str != '\n' && *str != '\0')
	{
		rgb = ft_split(str, ' ');
		if (!rgb)
			return (error_allocation(), 0);
		map[i].x = ft_atoi(rgb[0]) / 255.0 * 2 - 1;
		map[i].y = ft_atoi(rgb[1]) / 255.0 * 2 - 1;
		map[i].z = ft_atoi(rgb[2]) / 255.0 * 2 - 1;
		map[i] = normalize(map[i]);
		free(str);
		free_split(rgb);
		str = get_next_line(fd);
		i++;
	}
	
	if (str != NULL && (*str == '\n' || *str == '\0'))
		free(str);
	return (1);
}

int	get_width_height(int fd, int *width, int *height)
{
	char *str;
	int		i;

	i = 0;
	str = get_next_line(fd);
	if (!str)
		return (0);
	*width = ft_atoi(str);
	while (str[i] != ' ')
		i++;
	i++;
	*height = ft_atoi(&str[i]);
	free(str);
	return (1);
}

int	read_normal_map(t_normal_map *normal_map, char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nOne of the normal map file cannot be access.\n", 2), 1);
	if (!get_width_height(fd, &normal_map->width, &normal_map->height) || normal_map->width == 0 || normal_map->height == 0)
		return (error_allocation(), close(fd), 1);
	normal_map->map = malloc(sizeof(t_vec) * normal_map->width * normal_map->height);
	if (!normal_map->map)
		return (error_allocation(), close(fd), 1);
	if (!get_rgb_pixel_value(fd, normal_map->map))
		return (close(fd), 1);
	if (close(fd) == -1)
		return (ft_putstr_fd("Error\nOne of the normal map file cannot be closed.\n", 2), 1);
	return (0);
}

char	*good_file(int number)
{
	if (number == 0)
		return ("normal_maps/cliff");
	if (number == 1)
		return ("normal_maps/sand");
	if (number == 2)
		return ("normal_maps/terrain");
	if (number == 3)
		return ("normal_maps/tree");
	if (number == 4)
		return ("normal_maps/wood");
	return (NULL);
}

void	load_normal_maps(t_rt *rt, char **rows)
{
	int	*good_maps;
	int	i;

	rt->normal_maps = malloc(sizeof(t_normal_map) * NB_MAP);
    if (!rt->normal_maps)
        (free_split(rows), error_allocation(), exit(1));
	rt->nb_normal_maps = NB_MAP;
	set_maps(rt->normal_maps);
	good_maps = fill_good_maps(rows);
	if (good_maps == NULL)
		 (free_maps(rt->normal_maps), free_split(rows), exit(1));
	i = 0;
	while (i < NB_MAP)
	{
		if (good_maps[i])
			if (read_normal_map(rt->normal_maps + i, good_file(i)))
        		(free_maps(rt->normal_maps), free_split(rows), exit(1));	
		i++;
	}
}