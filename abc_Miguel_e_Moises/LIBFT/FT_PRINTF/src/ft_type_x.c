/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:37:40 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:37:43 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
// Creates nodes from type hexadecimal %x %X for printf function.

int	ft_type_x(t_list **lst, va_list ap, char type)
{
	t_list			*node;
	char			*str;
	size_t			n;
	unsigned int	i;

	node = NULL;
	n = va_arg(ap, unsigned int);
	if (n == 0)
		str = "0";
	else
		str = ft_dec2hex((size_t)n, type);
	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		node = ft_lstnew(ft_intdup((int)str[i]));
		if (node == NULL)
			return (0);
		ft_lstadd_back(lst, node);
		i++;
	}
	if (n != 0)
		free(str);
	return (1);
}
