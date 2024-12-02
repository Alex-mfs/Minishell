/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:36:32 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:36:36 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
// Creates a node of type char %c for printf function.

int	ft_type_c(t_list **lst, va_list ap)
{
	t_list	*node;
	int		*chr;

	node = NULL;
	chr = ft_intdup(va_arg(ap, int));
	node = ft_lstnew(chr);
	if (node == NULL)
		return (0);
	ft_lstadd_back(lst, node);
	return (1);
}
