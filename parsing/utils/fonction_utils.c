#include "minirt.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
			i++;
		i--;
		while (i >= 0)
		{
			free(split[i]);
			i--;
		}
		free(split);
	}
}

void	set_maps(t_normal_map *normal_maps)
{
	int	i;

	i = 0;
	while (i < NB_MAP)
	{
		normal_maps[i].map = NULL;
		i++;
	}
}

void	free_maps(t_normal_map *normal_maps, int *good_maps)
{
	int	i;

	i = 0;
	free(good_maps);
	while (i < NB_MAP)
	{
		if (normal_maps[i].map)
			(free(normal_maps[i].map), normal_maps[i].map = NULL);
		i++;
	}
	free(normal_maps);
}