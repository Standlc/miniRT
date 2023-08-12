/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:43 by stde-la-          #+#    #+#             */
/*   Updated: 2023/08/12 02:33:26 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int rgb_to_int(t_rgb rgb)
{
    unsigned char	r;
    unsigned char	g;
    unsigned char	b;

    r = min(rgb.r, 1.) * 255;
    g = min(rgb.g, 1.) * 255;
    b = min(rgb.b, 1.) * 255;
    return (r << 16 | g << 8 | b);
}

t_rgb	color_mult(t_rgb color_1, t_rgb color_2)
{
	color_1.r *= color_2.r;
	color_1.g *= color_2.g;
	color_1.b *= color_2.b;
	return (color_1);
}

t_rgb	color_add(t_rgb color_1, t_rgb color_2)
{
	color_1.r += color_2.r;
	color_1.g += color_2.g;
	color_1.b += color_2.b;
	return (color_1);
}

t_rgb	lerp_color(t_rgb c1, t_rgb c2, float t)
{
	c1.r = (1 - t) * c1.r + t * c2.r;
	c1.g = (1 - t) * c1.g + t * c2.g;
	c1.b = (1 - t) * c1.b + t * c2.b;
	return (c1);
}

t_rgb	color_fade(t_rgb color, float fade)
{
	color.r *= fade;
	color.g *= fade;
	color.b *= fade;
	return (color);
}
