#include "minirt.h"

int	handle_key_up(int key, t_rt *rt)
{
	if (key == CONTROL && rt->is_zoom_key_down)
	{
		rt->is_zoom_key_down = 0;
		rt->mouse.is_down = 0;
	}
	return (0);
}

void	print_cam_setup(t_cam *cam)
{
	printf("\n\n\t\tCamera setup\t\n\nPosition:\t");
	print_vector(cam->system.origin);
	printf("Direction:\t");
	print_vector(cam->dir);
	printf("\n");
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

int	set_hooks(t_rt *rt)
{
	mlx_hook(rt->win, ON_DESTROY, 0, close_program, rt);
	mlx_hook(rt->win, 2, 0, handle_key_down, rt);
	mlx_hook(rt->win, 3, 0, handle_key_up, rt);
	mlx_hook(rt->win, 4, 0, handle_mouse_down, rt);
	mlx_hook(rt->win, 5, 0, handle_mouse_up, rt);
	mlx_hook(rt->win, 6, 0, handle_mouse_move, rt);
	return (0);
}