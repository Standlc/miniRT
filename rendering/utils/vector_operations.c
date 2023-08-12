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

t_vec	scale(t_vec v, double coef)
{
	v.x *= coef;
	v.y *= coef;
	v.z *= coef;
	return (v);
}

t_vec	add(t_vec v1, t_vec v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

t_vec	sub(t_vec v1, t_vec v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return (v1);
}

t_vec	cross_product(t_vec *v1, t_vec *v2)
{
	t_vec	res;

	res.x = (v1->y * v2->z) - (v1->z * v2->y);
	res.y = - ((v1->x * v2->z) - (v1->z * v2->x));
	res.z = (v1->x * v2->y) - (v1->y * v2->x);
	return (normalize(res));
}
