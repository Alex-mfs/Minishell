/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:44:28 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:44:31 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Counts the number of nodes in a list
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*lst2;

	if (lst != NULL)
		size = 1;
	else
		return (0);
	lst2 = lst;
	while (lst2->next != NULL)
	{
		size++;
		lst2 = lst2->next;
	}
	return (size);
}
