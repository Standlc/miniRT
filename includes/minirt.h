/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:42:36 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/14 00:00:46 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

# include <X11/keysym.h>
# include <X11/X.h>

# include <X11/keysym.h>
# include <X11/X.h>

# include "structures.h"
# include "rendering.h"
# include "parsing.h"

int		close_program(t_rt *data);
void	free_elements(t_rt *rt);

#endif
