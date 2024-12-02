/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:49:12 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:49:16 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Creates a sub string from string s starting at the start index
#include "libft.h"

static void	ft_substrcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char	*ft_substr(const char*s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	s_len;
	size_t	substr_len;

	s_len = ft_strlen(s);
	if (s_len == 0 || start > s_len)
	{
		sub_s = ft_calloc(1, 1);
		return (sub_s);
	}
	if (len < (s_len - start))
		substr_len = len;
	else
		substr_len = s_len - start;
	sub_s = (char *)malloc(substr_len * sizeof(char) + 1);
	if (sub_s == NULL)
		return (NULL);
	else
	{
		ft_substrcpy(sub_s, &s[start], substr_len);
		return (sub_s);
	}
}
