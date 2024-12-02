/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:41:18 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:41:32 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Allocates memory for an array of nmemb elements of size size
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;	

	mem = malloc(nmemb * size);
	if (mem == NULL)
		return (NULL);
	else
	{
		ft_bzero(mem, nmemb * size);
		return (mem);
	}
}
