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
	v1.x = (1 - t) * v1.x + t * v2.x;
	v1.y = (1 - t) * v1.y + t * v2.y;
	v1.z = (1 - t) * v1.z + t * v2.z;
	return (v1);
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
	v.x *= 1.0 / len;
	v.y *= 1.0 / len;
	v.z *= 1.0 / len;
	return (v);
}

t_vec	get_ray_point(t_ray ray, double d)
{
	ray.dir.x = ray.dir.x * d + ray.origin.x;
	ray.dir.y = ray.dir.y * d + ray.origin.y;
	ray.dir.z = ray.dir.z * d + ray.origin.z;
	return (ray.dir);
}
