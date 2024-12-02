/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 01:56:38 by antfonse          #+#    #+#             */
/*   Updated: 2023/12/02 18:29:48 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Splits string s into several strings using character c as delimiter
#include "libft.h"

static unsigned int	str_n(const char *s, char c)
{
	unsigned int	i;
	unsigned int	n;
	unsigned int	word;

	i = 0;
	n = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && word == 0)
		{
			word = 1;
			n++;
		}
		if (s[i] == c && word == 1)
			word = 0;
		i++;
	}
	return (n);
}

static size_t	str_len(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static char	**free_array(char **strsplit, unsigned int j)
{
	while (j > 0)
	{
		j--;
		free(strsplit[j]);
	}
	free(strsplit);
	return (NULL);
}

static char	**split(char **strsplit, const char *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	word;

	i = 0;
	j = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && word == 0)
		{
			strsplit[j] = ft_substr(s, i, str_len(&s[i], c));
			if (strsplit[j] == NULL)
				return (free_array(strsplit, j));
			j++;
			word = 1;
		}
		if (s[i] == c && word == 1)
			word = 0;
		i++;
	}
	strsplit[j] = NULL;
	return (strsplit);
}

char	**ft_split(const char *s, char c)
{
	size_t			n;
	char			**strsplit;

	if (s == NULL)
		return (NULL);
	n = str_n(s, c);
	strsplit = (char **)malloc((n + 1) * sizeof(char *));
	if (strsplit == NULL)
		return (NULL);
	strsplit = split(strsplit, s, c);
	return (strsplit);
}
