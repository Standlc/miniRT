#include "minirt.h"

// IS THIS REALLY USEFUL??
void	free_object(t_material *object)
{
	free(object->shape);
}

void	free_elements(t_rt *rt)
{
	int	i;

	i = 0;
	while (i < rt->world.nb_objects)
	{
		free(rt->world.objects[i].shape);
		i++;
	}
	free(rt->world.objects);
	free(rt->world.lights);
	free(rt->pixel_buff);
	if (rt->mlx && rt->img.p)
		mlx_destroy_image(rt->mlx, rt->img.p);
	if (rt->mlx && rt->win)
		mlx_destroy_window(rt->mlx, rt->win);
	if (rt->mlx)
	{
		// mlx_destroy_display(rt->mlx);
		free(rt->mlx);
	}
}

void	free_normal_maps(t_rt *rt)
{
	int	i;

	i = 0;
	while (i < rt->nb_normal_maps)
	{
		free(rt->normal_maps[i].map);
		i++;
	}
	free(rt->normal_maps);
}

int	close_program(t_rt *rt)
{
	free_elements(rt);
	free_normal_maps(rt);
	printf("\n");
	exit(0);
}
