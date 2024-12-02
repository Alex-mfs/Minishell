/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_del_line_top.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/30 16:15:49 by joao-rib         ###   ########.fr       */
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

static char	**free_before_return(char **src, char **dest)
{
	free_all(src, 0);
	return (dest);
}

static int	countlines(char **src)
{
	int		w;

	w = 0;
	while (src[w])
		w++;
	return (w);
}

char	**ft_matrix_del_line_top(char **src)
{
	char	**dest;
	int		w;

	w = 0;
	if (src)
		w = countlines(src);
	if (w == 0)
		return (src);
	dest = ft_calloc(w, sizeof(char *));
	if (!dest)
		return (free_all(src, 0));
	dest[w - 1] = 0;
	if (w < 2)
		return (free_before_return(src, dest));
	w -= 2;
	while (w >= 0)
	{
		dest[w] = ft_strdup(src[w + 1]);
		if (!dest[w])
			return (free_all(dest, w + 1));
		w--;
	}
	if (src)
		free_all(src, 0);
	return (dest);
}
