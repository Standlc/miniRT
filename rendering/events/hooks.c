/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:05 by stde-la-          #+#    #+#             */
/*   Updated: 2023/09/11 12:44:43 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_hooks(t_rt *rt)
{
	mlx_hook(rt->win, ON_DESTROY, 0, close_program, rt);
	mlx_hook(rt->win, KEY_PRESS, KEY_PRESS_MASK, handle_key_down, rt);
	mlx_hook(rt->win, KEY_UP, KEY_UP_MASK, handle_key_up, rt);
	mlx_hook(rt->win, MOUSE_DOWN, MOUSE_DOWN_MASK, handle_mouse_down, rt);
	mlx_hook(rt->win, MOUSE_UP, MOUSE_UP_MASK, handle_mouse_up, rt);
	mlx_hook(rt->win, MOUSE_MOVE, MOUSE_MOVE_MASK, handle_mouse_move, rt);
	return (0);
}
