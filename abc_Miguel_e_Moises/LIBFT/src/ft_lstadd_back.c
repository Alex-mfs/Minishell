/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:42:45 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:42:48 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Adds a new node to the end of a chained list
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst2;

	if (new != NULL)
	{
		lst2 = ft_lstlast(*lst);
		if (lst2 == NULL)
			*lst = new;
		else
			lst2->next = new;
	}
}
