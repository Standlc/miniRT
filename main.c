/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:46:40 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/11 12:46:40 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_null(t_rt *rt)
{
	rt->mlx = NULL;
	rt->win = NULL;
	rt->world.objects = NULL;
	rt->world.lights = NULL;
	rt->pixel_buff = NULL;
	rt->img.p = NULL;
	rt->img.img_addr = NULL;
	rt->normal_maps = NULL;
	rt->mouse.is_down = 0;
	rt->is_zoom_key_down = 0;
}

int	init_mlx_window(t_rt *rt)
{
	rt->mlx = mlx_init();
	if (!rt->mlx)
		return (error_allocation(), free_elements(rt), 1);
	rt->win = mlx_new_window(rt->mlx, WIDTH, HEIGHT, "miniRT");
	rt->img.p = mlx_new_image(rt->mlx, WIDTH, HEIGHT);
	if (!rt->win || !rt->img.p)
		return (error_allocation(), free_elements(rt), 1);
	rt->img.img_addr = mlx_get_data_addr(rt->img.p, &rt->img.bpp,
			&rt->img.line_length, &rt->img.endian);
	if (!rt->img.img_addr)
		return (error_allocation(), free_elements(rt), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_rt	rt;

	set_null(&rt);
	parsing(argc, argv, &rt);
	if (init_mlx_window(&rt))
		return (1);
	rt.pixel_buff = malloc(sizeof(t_rgb) * HEIGHT * WIDTH);
	if (!rt.pixel_buff)
		return (error_allocation(), free_elements(&rt), 1);
	set_cam_system(&rt.world.cam);
	reset_rendering(&rt);
	set_hooks(&rt);
	mlx_loop_hook(rt.mlx, render, &rt);
	mlx_loop(rt.mlx);
	return (close_program(&rt), 0);
}
