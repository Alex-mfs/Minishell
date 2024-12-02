/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:43:21 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:43:27 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Frees node lst content using function del.
#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst != NULL)
	{
		del(lst->content);
		free(lst);
	}
	else
		free(lst);
}
