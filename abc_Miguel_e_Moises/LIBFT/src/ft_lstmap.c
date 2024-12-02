/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:44:08 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:44:11 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Iterates the chained list lst and applies function f on the content of
// each node. Creates a new list on the result. If needed, function del
// is used to delete the contents of a node.
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst2;
	t_list	*lstnew;
	t_list	*node;

	if (lst == NULL)
		return (NULL);
	lst2 = lst;
	lstnew = NULL;
	while (lst2->next != NULL )
	{
		node = ft_lstnew(f(lst2->content));
		if (node == NULL || node->content == NULL)
			ft_lstdelone(node, del);
		else
			ft_lstadd_back(&lstnew, node);
		lst2 = lst2->next;
	}
	node = ft_lstnew(f(lst2->content));
	if (node == NULL || node->content == NULL)
		ft_lstdelone(node, del);
	else
		ft_lstadd_back(&lstnew, node);
	return (lstnew);
}
