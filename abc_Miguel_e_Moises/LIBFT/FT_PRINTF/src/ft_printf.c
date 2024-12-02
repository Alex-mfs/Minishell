/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:35:41 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:35:45 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
// Replicates part of the standard function printf.

static void	ft_del(void *content)
{
	free(content);
}

static void	ft_putchar_ptr_fd(char *c, int fd)
{
	write(fd, c, 1);
}

int	ft_printf(const char *format, ...)
{
	unsigned int	len;
	int				state;
	t_list			*lst;
	va_list			ap;

	lst = NULL;
	va_start(ap, format);
	state = ft_strout(format, &lst, ap);
	va_end(ap);
	if (state == 0)
		return (-1);
	if (lst == NULL)
		return (0);
	ft_lstprint(lst, 1, &ft_putchar_ptr_fd);
	len = ft_lstsize(lst);
	ft_lstclear(&lst, &ft_del);
	return (len);
}
