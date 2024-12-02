/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:43:42 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:43:46 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Iterates the chained list lst and applies function f to each node content
#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*lst2;

	if (lst != NULL)
	{
		lst2 = lst;
		while (lst2->next != NULL )
		{
			f(lst2->content);
			lst2 = lst2->next;
		}
		f(lst2->content);
	}
}
