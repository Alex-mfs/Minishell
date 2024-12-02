/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:43:57 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:44:01 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Returns the last node of the chained list
#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*lst2;

	if (lst == NULL)
		return (lst);
	else
		lst2 = lst;
	while (lst2->next != NULL)
		lst2 = lst2->next;
	return (lst2);
}
