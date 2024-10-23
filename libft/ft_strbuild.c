/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbuild.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/10/23 02:48:49 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strbuild(char *s1, const char *s2)
// {
// 	char	*joined;
// 	size_t	l;
// 	size_t	l1;

// 	if (!s1)
// 	{
// 		s1 = malloc(1 * sizeof(char));
// 		s1[0] = '\0';
// 	}
// 	if (!s1 || !s2)
// 		return (NULL);
// 	l1 = ft_strlen(s1);
// 	l = l1 + ft_strlen(s2) + 1;
// 	joined = malloc(l * sizeof(char));
// 	if (!joined)
// 		return (NULL);
// 	joined[0] = '\0';
// 	ft_strlcat(joined, s1, l);
// 	ft_strlcat(joined, s2, l);
// 	free(s1);
// 	return (joined);
// }

#include "libft.h"

char	*ft_strbuild(char *s1, const char *s2)
{
	char	*joined;
	size_t	l;
	size_t	l1;

	if (!s1)
	{
		s1 = malloc(1 * sizeof(char));
		if (!s1)  // Verifique se a alocação foi bem-sucedida
			return (NULL);
		s1[0] = '\0';  // Inicialize s1 como uma string vazia
	}
	if (!s2)  // Verifique se s2 não é NULL
		return (s1);  // Se s2 for NULL, retorne s1

	// Calcular o tamanho necessário para a nova string
	l1 = ft_strlen(s1);
	l = l1 + ft_strlen(s2) + 1;

	// Alocar memória para a string concatenada
	joined = malloc(l * sizeof(char));
	if (!joined)
	{
		free(s1);  // Libere s1 se a alocação falhar
		return (NULL);
	}

	// Copiar s1 para a nova string e concatenar s2
	ft_strlcpy(joined, s1, l);  // Use strlcpy para copiar s1
	ft_strlcat(joined, s2, l);  // Use strlcat para concatenar s2

	// Liberar s1
	free(s1);

	// Retornar a string concatenada
	return (joined);
}
