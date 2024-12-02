/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:48:47 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:48:50 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Returns a pointer to the last occurrence of a character in a string
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_pos;	

	last_pos = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
			last_pos = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		last_pos = (char *)s;
	return (last_pos);
}
