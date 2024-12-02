/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strout.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:36:08 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:36:11 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
// Creates the output string (result string) from the application of printf

static void	ft_del(void *content)
{
	free(content);
}

static int	ft_stdnode(const char *format, unsigned int *i, t_list **lst)
{
	t_list	*node;
	int		*chr;

	node = NULL;
	chr = ft_intdup((int)format[*i]);
	node = ft_lstnew(chr);
	if (node == NULL)
		return (0);
	ft_lstadd_back(lst, node);
	return (1);
}

int	ft_strout(const char *format, t_list **lst, va_list ap)
{
	int				state;
	unsigned int	i;

	state = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
			state = ft_parsemarker(format, &i, lst, ap);
		else
			state = ft_stdnode(format, &i, lst);
		if (state == 0)
		{
			ft_lstclear(lst, &ft_del);
			return (0);
		}
		i++;
	}
	return (1);
}
