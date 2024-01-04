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
	rt->world.display_stars = 0;
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

void	*thread_routine(void *data)
{
	t_thread_data	*thread;
	int				curr_frame = 1;
	int				y;
	int				x;

	thread = (t_thread_data *)data;
	pthread_mutex_lock(&(thread->end_mutex));
	while (1)
	{
		pthread_mutex_lock(&(thread->thread_mutex));
		pthread_mutex_unlock(&(thread->end_mutex));

		pthread_mutex_lock(&(thread->rt->exit_mutex));
		int exit = thread->rt->exit;
		pthread_mutex_unlock(&(thread->rt->exit_mutex));
		if (exit)
		{
			pthread_mutex_unlock(&(thread->thread_mutex));
			return (NULL);
		}

		pthread_mutex_lock(&(thread->rt->rendering_frame_mutex));
		curr_frame = thread->rt->rendering_frame;
		// static int	curr_frame_cp = 1;
		// if (curr_frame != curr_frame_cp)
		// 	printf("%d %d\n", curr_frame, curr_frame_cp);
		// curr_frame_cp++;
		pthread_mutex_unlock(&(thread->rt->rendering_frame_mutex));

		y = 0;
		while (y < HEIGHT)
		{
			x = thread->id;
			while (x < WIDTH)
			{
				put_pixel(thread->rt, x, y, get_pixel_color(thread->rt, x, y, curr_frame));
				x += N_THREADS;
			}
			y += 1;
		}

		pthread_mutex_unlock(&(thread->thread_mutex));
		pthread_mutex_lock(&(thread->end_mutex));
		pthread_mutex_lock(&(thread->rt->start_mutex));
		pthread_mutex_unlock(&(thread->rt->start_mutex));
	}
	return (NULL);
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

	pthread_mutex_init(&rt.rendering_frame_mutex, NULL);
	pthread_mutex_init(&rt.start_mutex, NULL);
	pthread_mutex_init(&rt.exit_mutex, NULL);
	rt.exit = 0;

	int i = 0;
	while (i < N_THREADS)
	{
		rt.threads[i].is_frame_rendered = 0;
		rt.threads[i].id = i;
		rt.threads[i].rt = &rt;
		pthread_mutex_init(&rt.threads[i].thread_mutex, NULL);
		pthread_mutex_init(&rt.threads[i].end_mutex, NULL);
		pthread_create(&rt.threads[i].thread, NULL, thread_routine, rt.threads + i);
		i++;
	}

	mlx_loop_hook(rt.mlx, render, &rt);
	mlx_loop(rt.mlx);
	return (close_program(&rt), 0);
}
