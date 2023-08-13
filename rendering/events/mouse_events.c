/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:09 by stde-la-          #+#    #+#             */
/*   Updated: 2023/08/13 02:10:09 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_zoom(t_cam *cam, int mouse_dir_y)
{
	cam->system.origin =
		add(cam->system.origin, scale(cam->dir, -mouse_dir_y / 30.0));
}

void	rotate_camera(t_cam *cam, int mouse_dir_x, int mouse_dir_y)
{
	t_vec	x_dir;
	t_vec	y_dir;
	t_vec	new_cam_pos;

	x_dir = scale(cam->system.x, mouse_dir_x / 40.f);
	y_dir = scale(cam->system.y, mouse_dir_y / 40.f * -1);
	new_cam_pos = add(cam->system.origin, add(y_dir, x_dir));
	cam->dir = normalize(sub(cam->look_at, new_cam_pos));
	cam->system.origin =
		get_ray_point((t_ray){cam->look_at, cam->dir}, -cam->radius);
}

int	handle_mouse_up(int button, int x, int y, t_rt *rt)
{
	(void)x;
	(void)y;
	if (button == LEFT_CLICK && rt->mouse.is_down)
		rt->mouse.is_down = 0;
	return (0);
}

int	handle_mouse_move(int x, int y, t_rt *rt)
{
	int	mouse_dir_x;
	int	mouse_dir_y;

	if (!rt->mouse.is_down)
		return (0);
	mouse_dir_x = rt->mouse.origin.x - x;
	mouse_dir_y = rt->mouse.origin.y - y;
	if (mouse_dir_x == 0 && mouse_dir_y == 0)
		return (0);
	if (rt->is_zoom_key_down)
		handle_zoom(&(rt->world.cam), mouse_dir_y);
	else
		rotate_camera(&(rt->world.cam), mouse_dir_x, mouse_dir_y);
	set_cam_system(&(rt->world.cam));
	reset_rendering(rt);
	rt->mouse.origin.x = x;
	rt->mouse.origin.y = y;
	return (0);
}

int	handle_mouse_down(int button, int x, int y, t_rt *rt)
{
	float	horizontal;
	float	vertical;
	float	len_to_screen_center;
	t_cam	*cam;

	if (button != LEFT_CLICK)
		return (0);
	rt->mouse.is_down = 1;
	rt->mouse.origin = (t_vec2){x, y};
	if (rt->is_zoom_key_down)
		return (0);
	cam = &(rt->world.cam);
	horizontal = (float)x / WIDTH * 2 - 1;
	vertical = 1 - (float)y / HEIGHT * 2;
	len_to_screen_center = sqrt(horizontal * horizontal + vertical * vertical);
	cam->look_at =
		add(cam->system.origin, scale(cam->dir, len_to_screen_center * 40 + 2));
	cam->radius = vec_len(sub(cam->system.origin, cam->look_at));
	return (0);
}
