/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:45:20 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:45:23 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Copies the first n characters from source string to destination string
//(Can overlap)
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*desttmp;
	unsigned char	*srctmp;

	desttmp = (unsigned char *)dest;
	srctmp = (unsigned char *)src;
	if (desttmp < srctmp)
		return (ft_memcpy(dest, src, n));
	else
	{
		while (n > 0 && (dest || src))
		{
			desttmp[n - 1] = srctmp[n - 1];
			n--;
		}
		return (dest);
	}
}
