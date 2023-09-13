/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:54 by stde-la-          #+#    #+#             */
/*   Updated: 2023/08/11 14:44:10 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	dot(t_vec *v1, t_vec *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vec	cross_product(t_vec *v1, t_vec *v2)
{
	t_vec	res;

	res.x = (v1->y * v2->z) - (v1->z * v2->y);
	res.y = - ((v1->x * v2->z) - (v1->z * v2->x));
	res.z = (v1->x * v2->y) - (v1->y * v2->x);
	return (normalize(res));
}

t_vec	get_reflection(t_vec *v, t_vec *normal)
{
	return (*v - *normal * (2 * dot(v, normal)));
}

float	get_angle(t_vec *v1, t_vec *normalized)
{
	return (acosf(dot(v1, normalized) / vec_len(*v1)) * (180 / M_PI));
}

t_vec	project(t_vec projected, t_vec ref)
{
	return (ref * dot(&projected, &ref));
}
