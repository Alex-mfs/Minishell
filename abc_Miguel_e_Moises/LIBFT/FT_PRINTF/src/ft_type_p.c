/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:36:55 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:36:58 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
// Creates nodes from type pointer %p for printf function.

static char	*ft_nil(void)
{
	return ("(nil)");
}

int	ft_type_p(t_list **lst, va_list ap)
{
	t_list			*node;
	void			*ptr;
	char			*str;
	unsigned int	i;

	node = NULL;
	str = ft_nil();
	ptr = va_arg(ap, void *);
	if (ptr != NULL)
		str = ft_dec2hexptr((size_t)ptr, 'l');
	if (str == NULL)
		str = ft_nil();
	i = 0;
	while (str[i] != '\0')
	{
		node = ft_lstnew(ft_intdup((int)str[i]));
		if (node == NULL)
			return (0);
		ft_lstadd_back(lst, node);
		i++;
	}
	if (ptr != NULL)
		free(str);
	return (1);
}
