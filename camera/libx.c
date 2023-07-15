#include "minirt.h"

// void    move_light(int key, t_rt *rt)
// {
// 	static double  x = 0;

// 	// if (key == UP)
// 	// {
// 	// 	rt->lights[0].pos.x += cos(x) * 5;
// 	// 	// rt->lights[0].pos.y += sin(x) * 5;
// 	// 	rt->lights[0].pos.z -= sin(x) * 2;
// 	// 	// printf("%f\n", sin(x) * 5);
// 	// 	x += M_PI / 20;
// 	// }
// 	// else if (key == DOWN)
// 	// {
// 	// 	x -= M_PI / 20;
// 	// 	rt->lights[0].pos.x -= cos(x) * 5;
// 	// 	// rt->lights[0].pos.y -= sin(x) * 5;
// 	// 	rt->lights[0].pos.z += sin(x) * 2;
// 	// }
// }

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

int	handle_key(int key, t_rt *rt)
{
	// printf("%d\n", key);
	if (key == ESC)
		close_program(rt);
	return (0);
}

int	close_program(t_rt *rt)
{
	mlx_destroy_window(rt->mlx, rt->win);
	mlx_destroy_image(rt->mlx, rt->img.p);
	// mlx_destroy_display(rt->mlx);
	free(rt->mlx);
	free(rt->pixel_buff);
	exit (0);
}

t_rgb	gamma_correction(t_rgb *color, float gamma)
{
	color->r = pow(color->r, 1 / gamma);
	color->g = pow(color->g, 1 / gamma);
	color->b = pow(color->b, 1 / gamma);
	return (*color);
}

void	put_pixel(t_rt *rt, int x, int y, t_rgb color)
{
	char	*dst;

	// gamma_correction(&color, rt->opt.gamma);
	dst = rt->img.img_addr
		+ (y * rt->img.line_length + x * (rt->img.bpp / 8));
	*(unsigned int *)dst = rgb_to_int(color);
}

int handle_mouse_up(int button, int x, int y, t_rt *rt)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		stop_optimization(rt);
		rt->mouse.is_down = 0;
		rt->rendering_frame = 1;
		ft_memset(rt->pixel_buff, 0, HEIGHT * WIDTH * sizeof(t_rgb));
	}
	return (0);
} //MOUSE UP

int handle_mouse_move(int x, int y, t_rt *rt)
{
	int		mouse_dir_x;
	int		mouse_dir_y;
	float	radius_len;

	if (rt->mouse.is_down)
	{
		mouse_dir_x = rt->mouse.origin.x - x;
		mouse_dir_y = rt->mouse.origin.y - y;
		if (mouse_dir_x == 0 && mouse_dir_y == 0)
			return (0);

		radius_len = vec_len(sub(rt->cam.system.origin, rt->cam.look_at));
		t_vec	x_dir = scale(rt->cam.system.x, mouse_dir_x / 40.f);
		t_vec	y_dir = scale(rt->system.y, mouse_dir_y / 40.f * -1);
		t_vec	new_cam_pos = add(rt->cam.system.origin, add(y_dir, x_dir));
		t_vec	lookat_to_cam_pos = normalize(sub(new_cam_pos, rt->cam.look_at));
		lookat_to_cam_pos = get_ray_point((t_ray){rt->cam.look_at, lookat_to_cam_pos}, radius_len);
		rt->cam.system.origin = lookat_to_cam_pos;

		set_cam_system(rt);
		ft_memset(rt->pixel_buff, 0, HEIGHT * WIDTH * sizeof(t_rgb));
		rt->rendering_frame = 1;
		rt->mouse.origin.x = x;
		rt->mouse.origin.y = y;
	}
	return (0);
}

int handle_mouse(int event, int x, int y, t_rt *rt)
{
	if (event != 1 && event != 4 && event != 5)
		return (0);
	if (event == 1)
	{
		float	horizontal = (float)x / WIDTH * 2 - 1;
		float	vertical = 1 - (float)y / HEIGHT * 2;
		float	len_to_center = sqrt(horizontal * horizontal + vertical * vertical);

		start_optimization(rt);
		rt->mouse.is_down = 1;
		rt->mouse.origin = (t_point){x, y};
		rt->cam.look_at = add(rt->cam.system.origin, scale(rt->cam.system.z, len_to_center * 30 + 2));
		return (0);
	}
	else if (event == 4)
	{
		float	horizontal = (float)x / WIDTH * 2 - 1;
		float	vertical = 1 - (float)y / HEIGHT * 2;

		rt->cam.system.origin = add(rt->cam.system.origin, scale(rt->cam.system.y, vertical));
		rt->cam.look_at = add(rt->cam.look_at, scale(rt->cam.system.y, vertical));

		rt->cam.system.origin = add(rt->cam.system.origin, scale(rt->cam.system.x, horizontal));
		rt->cam.look_at = add(rt->cam.look_at, scale(rt->cam.system.x, horizontal));

		rt->cam.system.origin = add(rt->cam.system.origin, rt->cam.system.z);
		rt->cam.look_at = add(rt->cam.look_at, rt->cam.system.z);
	} // SCROLL UP
	else if (event == 5)
	{
		float	horizontal = (float)x / WIDTH * 2 - 1;
		float	vertical = 1 - (float)y / HEIGHT * 2;

		rt->cam.system.origin = sub(rt->cam.system.origin, scale(rt->cam.system.y, vertical));
		rt->cam.look_at = sub(rt->cam.look_at, scale(rt->cam.system.y, vertical));

		rt->cam.system.origin = sub(rt->cam.system.origin, scale(rt->cam.system.x, horizontal));
		rt->cam.look_at = sub(rt->cam.look_at, scale(rt->cam.system.x, horizontal));

		rt->cam.system.origin = sub(rt->cam.system.origin, rt->cam.system.z);
		rt->cam.look_at = sub(rt->cam.look_at, rt->cam.system.z);
	} // SCROLL DOWN
		ft_memset(rt->pixel_buff, 0, HEIGHT * WIDTH * sizeof(t_rgb));
	set_cam_system(rt);
	rt->rendering_frame = 1;
	return (0);
}