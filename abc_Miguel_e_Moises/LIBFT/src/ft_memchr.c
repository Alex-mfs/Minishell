/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:44:40 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:44:42 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Scans n bytes of memory area s to look for c character
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_tmp;
	unsigned int	i;

	s_tmp = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (s_tmp[i] == (unsigned char)c)
			return (s_tmp + i);
		i++;
	}
	return (NULL);
}
