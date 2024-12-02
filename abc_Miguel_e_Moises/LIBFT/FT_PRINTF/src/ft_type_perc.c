/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_perc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:37:06 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:37:09 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
// Creates a node of type char %c for printf function.

int	ft_type_perc(t_list **lst)
{
	t_list	*node;
	int		*chr;

	node = NULL;
	chr = ft_intdup('%');
	node = ft_lstnew(chr);
	if (node == NULL)
		return (0);
	ft_lstadd_back(lst, node);
	return (1);
}
