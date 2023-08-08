#include "minirt.h"

int handle_mouse_up(int button, int x, int y, t_rt *rt)
{
	(void)x;
	(void)y;
	if (button == LEFT_CLICK && rt->mouse.is_down)
		rt->mouse.is_down = 0;
	return (0);
}

void	handle_zoom(t_world *world, int mouse_dir_y)
{
	world->cam.system.origin = add(world->cam.system.origin, scale(world->cam.dir, -mouse_dir_y / 30.0));
}

void	rotate_camera(t_world *world, int mouse_dir_x, int mouse_dir_y)
{
	t_vec	x_dir;
	t_vec	y_dir;
	t_vec	new_cam_pos;

	x_dir = scale(world->cam.system.x, mouse_dir_x / 40.f);
	y_dir = scale(world->cam.system.y, mouse_dir_y / 40.f * -1);
	new_cam_pos = add(world->cam.system.origin, add(y_dir, x_dir));
	world->cam.dir = normalize(sub(world->cam.look_at, new_cam_pos));
	world->cam.system.origin = get_ray_point((t_ray){world->cam.look_at, world->cam.dir}, -world->cam.radius);
}

int handle_mouse_move(int x, int y, t_rt *rt)
{
	int		mouse_dir_x;
	int		mouse_dir_y;

	if (!rt->mouse.is_down)
		return (0);

	mouse_dir_x = rt->mouse.origin.x - x;
	mouse_dir_y = rt->mouse.origin.y - y;
	if (mouse_dir_x == 0 && mouse_dir_y == 0)
		return (0);

	if (rt->is_zoom_key_down)
		handle_zoom(&(rt->world), mouse_dir_y);
	else
		rotate_camera(&(rt->world), mouse_dir_x, mouse_dir_y);

	set_cam_system(&(rt->world));
	reset_rendering(rt);
	rt->mouse.origin.x = x;
	rt->mouse.origin.y = y;
	return (0);
}

int	handle_mouse_down(int button, int x, int y, t_rt *rt)
{
	float	horizontal;
	float	vertical;
	float	len_to_center;

	if (button != LEFT_CLICK)
		return (0);

	rt->mouse.is_down = 1;
	rt->mouse.origin = (t_vec2){x, y};
	if (rt->is_zoom_key_down)
		return (0);

	horizontal = (float)x / WIDTH * 2 - 1;
	vertical = 1 - (float)y / HEIGHT * 2;
	len_to_center = sqrt(horizontal * horizontal + vertical * vertical);
	rt->world.cam.look_at = add(rt->world.cam.system.origin, scale(rt->world.cam.dir, len_to_center * 40 + 2));
	rt->world.cam.radius = vec_len(sub(rt->world.cam.system.origin, rt->world.cam.look_at));
	return (0);
}
