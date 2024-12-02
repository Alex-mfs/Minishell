/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:47:27 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:47:30 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Concatenates one string (dst) with another (src).
// Null terminates the dest string and do not overflows
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_size;
	size_t	src_size;
	size_t	total_size;
	size_t	i;

	dest_size = ft_strlen(dest);
	src_size = ft_strlen(src);
	if (size == 0)
		return (src_size);
	if (dest_size < size)
		total_size = dest_size + src_size;
	else
		total_size = size + src_size;
	i = dest_size;
	while (i < (size - 1) && *src != '\0')
	{
		dest[i] = *src;
		i++;
		src++;
	}
	if (dest_size < size)
		dest[i] = '\0';
	return (total_size);
}
