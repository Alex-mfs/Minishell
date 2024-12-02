/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extras_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:13:27 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/20 17:14:15 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*copy;
	size_t	i;

	copy = malloc((n + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < n && s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strtok(char *str, const char *sep)
{
	static char	*stock;
	char		*token_start;

	if (str != NULL)
		stock = str;
	if (stock == NULL || *stock == '\0')
		return (NULL);
	while (*stock && ft_strchr(sep, *stock))
		stock++;
	if (*stock == '\0')
		return (NULL);
	token_start = stock;
	while (*stock && !ft_strchr(sep, *stock))
		stock++;
	if (*stock != '\0')
	{
		*stock = '\0';
		stock++;
	}
	return (token_start);
}
