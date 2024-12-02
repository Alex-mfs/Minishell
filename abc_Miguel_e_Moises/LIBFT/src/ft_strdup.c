/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:46:52 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:46:56 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Returns a pointer to a new string which is a duplicate of the string s
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*s2;
	size_t	s_len;

	s_len = ft_strlen(s);
	s2 = (char *)malloc(s_len * sizeof(char) + 1);
	if (s2 != NULL)
	{
		ft_strlcpy(s2, s, s_len + 1);
		return (s2);
	}
	return (NULL);
}
