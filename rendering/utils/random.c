/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:50 by stde-la-          #+#    #+#             */
/*   Updated: 2023/09/11 12:36:22 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	randf(void)
{
	return ((float)rand() / (float)RAND_MAX);
}

float	normal_randf(void)
{
	float	theta;
	float	rho;

	theta = 2 * M_PI * randf();
	rho = sqrtf(-2 * logf(randf()));
	return (rho * cos(theta));
}

t_vec	random_dir(void)
{
	return (normalize((t_vec){normal_randf(), normal_randf(), normal_randf()}));
}

t_vec	cosine_hemisphere_dir(t_vec *normal_dir)
{
	return (normalize(add(random_dir(), *normal_dir)));
}
