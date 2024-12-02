/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:35:03 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:35:09 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
// Outputs a linked list of any kind to the given file descriptor.

void	ft_lstprint(t_list *lst, int fd, void (*ft_printtype)(char *, int))
{
	ft_printtype((char *)lst->content, fd);
	while (lst->next)
	{
		lst = lst->next;
		ft_printtype((char *)lst->content, fd);
	}
}
