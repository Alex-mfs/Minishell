/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:49:02 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:49:04 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Returns a copy of string s1 with the characters of set removed from
// the beginning and the end of the string
#include "libft.h"

static unsigned int	ft_start(const char *s1, const char *set)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	start;

	i = 0;
	start = 0;
	while (i < ft_strlen(s1))
	{
		j = 0;
		while (j < ft_strlen(set))
		{
			if (s1[i] == set[j])
			{
				start++;
				break ;
			}
			j++;
		}
		i++;
		if (start < i)
			break ;
	}
	return (start);
}

static size_t	ft_len(const char *s1, const char *set, unsigned int start)
{
	unsigned int	i;
	unsigned int	j;
	size_t			len;
	size_t			s1_len;

	i = 1;
	s1_len = ft_strlen(s1);
	len = s1_len - start;
	while (i < (s1_len - start))
	{
		j = 0;
		while (j < ft_strlen(set))
		{
			if (s1[s1_len - i] == set[j])
			{
				len--;
				break ;
			}
			j++;
		}
		if ((len + start) > (s1_len - i))
			break ;
		i++;
	}
	return (len);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	unsigned int	start;
	size_t			len;

	if (s1 == NULL || ft_strlen(s1) == 0)
		return (ft_calloc(1, 1));
	start = ft_start(s1, set);
	len = ft_len(s1, set, start);
	return (ft_substr(s1, start, len));
}
