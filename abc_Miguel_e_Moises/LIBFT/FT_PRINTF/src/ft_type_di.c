/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_di.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:36:43 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:36:47 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
// Creates nodes from type signed decimal integer %d and %i
// for printf function.

int	ft_type_di(t_list **lst, va_list ap)
{
	t_list			*node;
	char			*str;
	unsigned int	i;

	str = ft_itoa(va_arg(ap, int));
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
