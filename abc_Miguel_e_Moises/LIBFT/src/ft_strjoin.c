/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:47:16 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:47:19 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Creates a new string which is the result of the concatenation 
// of string s1 and s2 in this order
#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*s3;
	size_t	len;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	s3 = (char *)malloc(len * sizeof(char) + 1);
	if (s3 == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		s3[i] = s1[i];
		i++;
	}
	while (*s2 != '\0')
	{
		s3[i] = *s2;
		i++;
		s2++;
	}
	s3[i] = '\0';
	return (s3);
}
