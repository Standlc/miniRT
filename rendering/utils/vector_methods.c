/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_methods.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:52 by stde-la-          #+#    #+#             */
/*   Updated: 2023/08/12 01:26:53 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec  get_reflection(t_vec *v, t_vec *normal)
{
	return (sub(*v, scale(*normal, 2 * dot(v, normal))));
}

float	get_angle(t_vec *v1, t_vec *normalized)
{
	return (acosf(dot(v1, normalized) / vec_len(*v1)) * (180 / M_PI));
}

// float	get_angle(t_vec *v1, t_vec *v2)
// {
// 	return (acosf(dot(v1, v2) / (vec_len(*v1) * vec_len(*v2))) * (180 / M_PI));
// }

t_vec	project(t_vec projected, t_vec ref)
{
	return (scale(ref, dot(&projected, &ref)));
}
