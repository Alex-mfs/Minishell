/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:47:38 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:47:40 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Copies a set number of characters from src to dst
// Null terminates the dest string and do not overflows
#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_count;

	src_count = ft_strlen(src);
	while (size > 1 && *src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
		size--;
	}
	if (size > 0)
		*dest = '\0';
	return (src_count);
}
