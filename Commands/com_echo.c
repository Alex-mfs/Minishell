/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:20:41 by alfreire          #+#    #+#             */
/*   Updated: 2024/11/28 14:36:22 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_valid(char *word)
{
	int	j;

	j = 1;
	while (word[j])
	{
		if (word[j] == 'n')
			return (true);
		j++;
	}
	return (false);
}

void	echo(char **words)
{
	int		i;
	bool	only_n;

	i = 0;
	only_n = true;
	while (words[i] && words[i][0] == '-')
	{
		if (is_valid(words[i]))
			only_n = false;
		i++;
	}
	while (words[i])
	{
		printf("%s", words[i]);
		i++;
		if (words[i])
			printf(" ");
	}
	if (only_n)
		printf("\n");
}
