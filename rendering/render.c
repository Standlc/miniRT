/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:47:00 by stde-la-          #+#    #+#             */
/*   Updated: 2023/09/11 12:34:30 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define INTERVAL 5

void	put_pixel(t_rt *rt, int x, int y, t_rgb color)
{
	char	*dst;

	dst = rt->img.img_addr
		+ (y * rt->img.line_length + x * (rt->img.bpp / 8));
	*(unsigned int *)dst = rgb_to_int(color);
}

t_vec	to_world_coordinates(t_cam *cam, double x, double y)
{
	float	tan_view_field;

	tan_view_field = tanf(cam->field_view / 2 * M_PI / 180);
	x = (2 * (x + 0.5) / WIDTH - 1) * tan_view_field;
	y = (1 - 2 * (y + 0.5) / HEIGHT) * tan_view_field * ((float)HEIGHT / WIDTH);
	return (system_transform(&(t_vec){x, y, 1.0}, &(cam->system)));
}

void	set_cam_ray(t_world *world, t_ray *cam_ray, int x, int y)
{
	t_vec	world_pixel;
	t_vec2	blur;

	blur.x = randf() * CAM_FUZZ - CAM_FUZZ / 2;
	blur.y = randf() * CAM_FUZZ - CAM_FUZZ / 2;
	cam_ray->origin = world->cam.system.origin;
	world_pixel = to_world_coordinates(&(world->cam), x + blur.x, y + blur.y);
	cam_ray->dir = normalize(sub(world_pixel, cam_ray->origin));
}

t_rgb	get_pixel_color(t_rt *rt, int x, int y, int curr_frame)
{
	t_ray	cam_ray;
	t_rgb	pixel_color;

	set_cam_ray(&(rt->world), &cam_ray, x, y);
	pixel_color = cast_ray(&(rt->world), &cam_ray, 0, 1);
	rt->pixel_buff[y * WIDTH + x]
		= color_add(rt->pixel_buff[y * WIDTH + x], pixel_color);
	return (color_fade(rt->pixel_buff[y * WIDTH + x], 1.f / curr_frame));
}

int	render(t_rt *rt)
{
	int	curr_frame;
	int	y;
	int	x;

	curr_frame = (rt->rendering_frame - 1) / INTERVAL + 1;
	if (curr_frame > RPP)
		return (0);
	y = 0;
	while (y < HEIGHT)
	{
		x = (rt->rendering_frame - 1) % INTERVAL;
		while (x < WIDTH)
		{
			put_pixel(rt, x, y, get_pixel_color(rt, x, y, curr_frame));
			x += INTERVAL;
		}
		y += 1;
	}
	loading_bar(RPP, curr_frame);
	rt->rendering_frame += 1;
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img.p, 0, 0);
	return (0);
}
