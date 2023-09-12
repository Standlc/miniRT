/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:46:49 by stde-la-          #+#    #+#             */
/*   Updated: 2023/09/11 12:38:22 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	pow2(double n)
{
	return (n * n);
}

double	relu(double n)
{
	if (n > 0.0)
		return (n);
	return (0.0);
}

double	min(double a, double b)
{
	if (a > b)
		return (b);
	return (a);
}

double	max(double a, double b)
{
	if (a < b)
		return (b);
	return (a);
}

int	solve_quadratic(t_quadratic *f)
{
	double	discr;
	double	res;

	discr = (f->b * f->b) - 4 * f->a * f->c;
	if (discr < 0.0)
		return (0);
	if (discr == 0.0)
	{
		f->t_1 = -0.5 * f->b / f->a;
		f->t_2 = f->t_1;
	}
	else
	{
		if (f->b > 0.0)
			res = -0.5 * (f->b + sqrt(discr));
		else
			res = -0.5 * (f->b - sqrt(discr));
		f->t_1 = res / f->a;
		f->t_2 = f->c / res;
	}
	return (1);
}
