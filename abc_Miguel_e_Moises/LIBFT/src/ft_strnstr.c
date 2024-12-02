/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:48:34 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:48:37 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Searches for the first occurrence of str little
// in the first n characters of str big.
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*big_tmp;
	char			*little_tmp;

	if (*little == '\0')
		return ((char *)big);
	big_tmp = (char *)big;
	little_tmp = (char *)little;
	i = 0;
	while (i < len && big_tmp[i] != '\0')
	{
		j = 0;
		while (big_tmp[i + j] == little_tmp[j] && (i + j) < len)
		{
			j++;
			if (little_tmp[j] == '\0')
				return (&big_tmp[i]);
		}
		i++;
	}
	return (NULL);
}
