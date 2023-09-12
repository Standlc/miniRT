/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:42 by stde-la-          #+#    #+#             */
/*   Updated: 2023/09/11 12:40:39 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	color_sub(t_rgb color, float sub)
{
	color.r = max(color.r - sub, 0.0);
	color.g = max(color.g - sub, 0.0);
	color.b = max(color.b - sub, 0.0);
	return (color);
}

t_rgb	ambient_light(t_rgb *color, t_ray *ray, float intensity)
{
	t_rgb	darker;

	darker = color_sub(*color, 1 - intensity);
	return (lerp_color(
			lerp_color(darker, (t_rgb){1.f, 1.f, 1.f}, intensity),
		lerp_color(darker, *color, intensity),
		ray->dir.y * 0.5 + 0.5));
}
