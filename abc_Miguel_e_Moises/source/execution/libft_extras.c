/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:35:30 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/20 17:14:59 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*ft_strsep(char **str, const char *delim)
{
	size_t	i;
	char	*token;
	char	*next;

	token = *str;
	if (token)
	{
		i = ft_strcspn(token, delim);
		next = NULL;
		if (token[i])
		{
			token[i] = '\0';
			next = &token[i + 1];
		}
		*str = next;
	}
	return (token);
}

size_t	ft_strcspn(const char *s1r, const char *s2r)
{
	const char	*s1;
	const char	*s2;

	s1 = s1r;
	while (*s1)
	{
		s2 = s2r;
		while (*s2)
		{
			if (*s1 == *s2++)
				return (s1 - s1r);
		}
		s1++;
	}
	return (s1 - s1r);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
