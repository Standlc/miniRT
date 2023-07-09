/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:49:53 by svan-de-          #+#    #+#             */
/*   Updated: 2022/11/17 15:19:12 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst0;
	t_list	*first;

	if (!lst || !f)
		return (NULL);
	lst0 = ft_lstnew(f(lst->content));
	if (!lst0)
		return (NULL);
	lst = lst->next;
	first = lst0;
	while (lst)
	{
		lst0->next = ft_lstnew(f(lst->content));
		if (!(lst0->next))
			return (ft_lstclear(&first, del), NULL);
		lst = lst->next;
		lst0 = lst0->next;
	}
	lst0 = first;
	return (lst0);
}
