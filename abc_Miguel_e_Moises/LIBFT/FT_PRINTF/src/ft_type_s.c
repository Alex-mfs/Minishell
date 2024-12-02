/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:37:16 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:37:19 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
// Creates nodes from type str %s for printf function.

int	ft_type_s(t_list **lst, va_list ap)
{
	t_list			*node;
	char			*str;
	char			*str_null;

	node = NULL;
	str_null = "(null)";
	str = va_arg(ap, char *);
	if (str == NULL)
		str = str_null;
	while (*str != '\0')
	{
		node = ft_lstnew(ft_intdup((int)*str));
		if (node == NULL)
			return (0);
		ft_lstadd_back(lst, node);
		str++;
	}
	return (1);
}
