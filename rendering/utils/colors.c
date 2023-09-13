/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:43 by stde-la-          #+#    #+#             */
/*   Updated: 2023/09/11 12:56:25 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rgb_to_int(t_rgb rgb)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = min(rgb.r, 1.) * 255;
	g = min(rgb.g, 1.) * 255;
	b = min(rgb.b, 1.) * 255;
	return (r << 16 | g << 8 | b);
}

t_rgb	lerp_color(t_rgb c1, t_rgb c2, float t)
{
	return ((1 - t) * c1 + t * c2);
}
