/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:36 by stde-la-          #+#    #+#             */
/*   Updated: 2023/09/11 12:41:37 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	intersect_circle(t_ray *ray, void *shape, double *t, int *is_surface_hit)
{
	t_circle	*circle;
	t_vec		hit_point;

	(void)is_surface_hit;
	circle = (t_circle *)shape;
	if (!intersect_plane(ray, (void *)&(circle->plane), t, NULL))
		return (0);
	hit_point = get_ray_point(*ray, *t);
	if (vec_len(sub(hit_point, circle->plane.point)) <= circle->radius)
		return (1);
	*t = 0.0;
	return (0);
}
