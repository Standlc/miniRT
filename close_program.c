/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:46:01 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/14 00:01:31 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_normal_maps(t_rt *rt)
{
	int	i;

	i = 0;
	while (i < rt->nb_normal_maps)
	{
		if (rt->normal_maps && rt->normal_maps[i].map)
			(free(rt->normal_maps[i].map), rt->normal_maps[i].map = NULL);
		i++;
	}
	free(rt->normal_maps);
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
		//mlx_destroy_display(rt->mlx);
		free(rt->mlx);
	}
	free_normal_maps(rt);
}

int	close_program(t_rt *rt)
{
	pthread_mutex_lock(&(rt->exit_mutex));
	rt->exit = 1;
	pthread_mutex_unlock(&(rt->exit_mutex));
	int	i = 0;
	while (i < N_THREADS)
	{
		pthread_join(rt->threads[i].thread, NULL);
		i++;
	}

	free_elements(rt);
	printf("\n");
	exit(0);
}
