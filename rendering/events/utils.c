#include "minirt.h"

void	reset_rendering(t_rt *rt)
{
	ft_memset(rt->pixel_buff, 0, HEIGHT * WIDTH * sizeof(t_rgb));
	rt->rendering_frame = 1;
}

void	stop_optimization(t_rt *rt)
{
	// rt->opt.rpp = RPP;
	rt->opt.max_depth = MAX_DEPTH;
	rt->opt.pixel_rendered_interval = 1;
}

void	start_optimization(t_rt *rt)
{
	// rt->opt.rpp = 1;
	rt->opt.max_depth = 1;
	rt->opt.pixel_rendered_interval = 3;
}

void	free_object(t_material *object)
{
	free(object->shape);
}

void	free_elements(t_rt *rt)
{
	int	i;

	i = rt->nb_objects - 1;
	while (i >= 0)
	{
		free_object(rt->objects + i);
		i--;
	}
	free(rt->objects);
	free(rt->lights);
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
