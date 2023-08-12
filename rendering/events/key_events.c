/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:07 by stde-la-          #+#    #+#             */
/*   Updated: 2023/08/10 15:46:08 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_cam_setup(t_cam *cam)
{
	printf("\n\n\t\tCamera setup\t\n\nPosition:\t");
	print_vector(cam->system.origin);
	printf("Direction:\t");
	print_vector(cam->dir);
	printf("\n");
}

int	handle_key_up(int key, t_rt *rt)
{
	if (key == CONTROL && rt->is_zoom_key_down)
	{
		rt->is_zoom_key_down = 0;
		rt->mouse.is_down = 0;
	}
	return (0);
}

int	handle_key_down(int key, t_rt *rt)
{
	if (key == CONTROL && !rt->mouse.is_down)
		rt->is_zoom_key_down = 1;
	else if (key == ESC)
		close_program(rt);
	else if (key == PRINT)
		print_cam_setup(&(rt->world.cam));
	return (0);
}
