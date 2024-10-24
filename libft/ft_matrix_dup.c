/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/10/24 11:37:57 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

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

char	**ft_matrix_dup(char **src)
{
	char	**dest;
	int		w;

	w = 0;
	while (src[w])
		w++;
	dest = ft_calloc(w + 1, sizeof(char *));
	if (!dest)
		return (NULL);
	//dest[w] = 0;
	w--;
	while (w >= 0)
	{
		dest[w] = ft_strdup(src[w]);
		if (!dest[w])
			return (free_all(dest, w + 1));
		w--;
	}
	return (dest);
}
