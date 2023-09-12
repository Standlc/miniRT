/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_methods.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:52 by stde-la-          #+#    #+#             */
/*   Updated: 2023/09/11 12:35:56 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	get_reflection(t_vec *v, t_vec *normal)
{
	return (sub(*v, scale(*normal, 2 * dot(v, normal))));
}

float	get_angle(t_vec *v1, t_vec *normalized)
{
	return (acosf(dot(v1, normalized) / vec_len(*v1)) * (180 / M_PI));
}

t_vec	project(t_vec projected, t_vec ref)
{
	return (scale(ref, dot(&projected, &ref)));
}
