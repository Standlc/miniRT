#include "minirt.h"

void	reset_rendering(t_rt *rt)
{
	rt->rendering_frame = 1;
	ft_memset(rt->pixel_buff, 0, HEIGHT * WIDTH * sizeof(t_rgb));
	ft_memset(rt->img.img_addr, 0, HEIGHT * WIDTH * (rt->img.bpp / 8));
}

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
	// if (rt->mlx)
	// 	(mlx_destroy_display(rt->mlx), free(rt->mlx));
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
	exit(0);
}

void	put_pixel(t_rt *rt, int x, int y, t_rgb color)
{
	char	*dst;

	dst = rt->img.img_addr
		+ (y * rt->img.line_length + x * (rt->img.bpp / 8));
	*(unsigned int *)dst = rgb_to_int(color);
}
