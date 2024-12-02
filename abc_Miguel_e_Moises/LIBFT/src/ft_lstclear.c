/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:43:05 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:43:09 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// Deletes and frees the given node and any successor using function del.
// Sets the pointer to the list to NULL

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*lst0;
	t_list	*lst1;

	if (*lst != NULL)
	{
		lst0 = *lst;
		lst1 = lst0->next;
		while (lst1 != NULL)
		{
			del(lst0->content);
			free(lst0);
			lst0 = lst1;
			lst1 = lst1->next;
		}
		del(lst0->content);
		free(lst0);
		*lst = NULL;
	}
}
