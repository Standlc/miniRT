/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:56 by stde-la-          #+#    #+#             */
/*   Updated: 2023/09/11 12:48:51 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_vector(t_vec v)
{
	printf("%.1f,%.1f,%.1f\n", v.x, v.y, v.z);
}

t_vec	lerp(t_vec v1, t_vec v2, float t)
{
	return ((1 - t) * v1 + t * v2);
}

double	vec_len(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec	normalize(t_vec v)
{
	double	len;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (len == 0.0)
		return (v);
	return (v / len);
}

t_vec	get_ray_point(t_ray ray, double d)
{
	return (ray.dir * d + ray.origin);
}
