/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:45:09 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:45:12 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Copies the first n characters from source string to destination string
// (No overlap)
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*memdest;
	unsigned char	*memsrc;

	memdest = (unsigned char *)dest;
	memsrc = (unsigned char *)src;
	while (n > 0 && (dest || src))
	{
		*memdest = *memsrc;
		memdest++;
		memsrc++;
		n--;
	}
	return (dest);
}
