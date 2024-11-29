/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat_add_safe_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/29 01:35:38 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_all(char **tab, int w)
{
	while (tab[w])
	{
		free(tab[w]);
		w++;
	}
	free(tab[w]);
	free(tab);
	return (NULL);
}

static int	countlines(char **src)
{
	int		w;

	w = 0;
	while (src[w])
		w++;
	return (w);
}

static bool	fill_matrix(char **src, char **dest, int w)
{
	while (w >= 0)
	{
		dest[w] = ft_strdup(src[w]);
		if (!dest[w])
		{
			free_all(dest, w + 1);
			return (false);
		}
		w--;
	}
	return (true);
}

char	**ft_mat_add_safe_line(char **src, char *newline)
{
	char	**dest;
	int		w;

	w = 0;
	if (!newline[0])
	{
		free(newline);
		return (src);
	}
	if (src)
		w = countlines(src);
	dest = ft_calloc(w + 2, sizeof(char *));
	if (!dest)
		return (NULL);
	dest[w + 1] = 0;
	dest[w] = ft_strdup(newline);
	free(newline);
	if (!fill_matrix(src, dest, w - 1))
		return (NULL);
	if (src)
		free_all(src, 0);
	return (dest);
}
