/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:02:00 by svan-de-          #+#    #+#             */
/*   Updated: 2022/11/15 15:08:03 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst0;

	if (lst && !*lst)
		*lst = new;
	else
	{	
		lst0 = ft_lstlast(*lst);
		lst0->next = new;
	}
}
