/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:45:32 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:45:36 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Replaces the first n characters of a memory area by the input character
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*mem;

	mem = (unsigned char *)s;
	while (n > 0)
	{
		*mem = (unsigned char)c;
		mem++;
		n--;
	}
	return (s);
}
