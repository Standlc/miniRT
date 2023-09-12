/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinate_system.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:45 by stde-la-          #+#    #+#             */
/*   Updated: 2023/09/11 12:56:12 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_cam_system(t_cam *cam)
{
	cam->system.z = cam->dir;
	if (fabs(dot(&(t_vec){0, 1, 0}, &(cam->system.z))) < 1.0)
		cam->system.x = cross_product(&(t_vec){0, 1, 0}, &(cam->system.z));
	else
		cam->system.x = cross_product(&(t_vec){0, 0, 1}, &(cam->system.z));
	cam->system.y = cross_product(&(cam->system.z), &(cam->system.x));
}

t_vec	system_transform(t_vec *v, t_system *system)
{
	t_vec	result;

	result.x = v->x * system->x.x + v->y * system->y.x + v->z * system->z.x
		+ system->origin.x;
	result.y = v->x * system->x.y + v->y * system->y.y + v->z * system->z.y
		+ system->origin.y;
	result.z = v->x * system->x.z + v->y * system->y.z + v->z * system->z.z
		+ system->origin.z;
	return (result);
}

t_system	create_system(t_vec up)
{
	t_system	system;

	up = normalize(up);
	system.y = up;
	if (fabs(dot(&(t_vec){0, 0, 1}, &up)) < 1)
		system.x = cross_product(&up, &(t_vec){0, 0, 1});
	else
		system.x = cross_product(&up, &(t_vec){0, 1, 0});
	system.z = cross_product(&(system.x), &(system.y));
	return (system);
}
