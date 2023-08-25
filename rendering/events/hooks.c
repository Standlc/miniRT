/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:05 by stde-la-          #+#    #+#             */
/*   Updated: 2023/08/10 15:46:05 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_hooks(t_rt *rt)
{
	mlx_hook(rt->win, ON_DESTROY, 0, close_program, rt);
	mlx_hook(rt->win, KeyPress, KeyPressMask, handle_key_down, rt);
	mlx_hook(rt->win, KeyRelease, KeyReleaseMask, handle_key_up, rt);
	mlx_hook(rt->win, ButtonPress, ButtonPressMask, handle_mouse_down, rt);
	mlx_hook(rt->win, ButtonRelease, ButtonReleaseMask, handle_mouse_up, rt);
	mlx_hook(rt->win, MotionNotify, PointerMotionMask, handle_mouse_move, rt);
	return (0);
}