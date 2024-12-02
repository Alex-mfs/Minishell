/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:37:27 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:37:30 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
// Creates nodes from type unsigned decimal integer %u for printf function.

int	ft_type_u(t_list **lst, va_list ap)
{
	t_list			*node;
	char			*str;
	unsigned int	i;

	str = ft_itoa_u(va_arg(ap, unsigned int));
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
	free(str);
	return (1);
}
