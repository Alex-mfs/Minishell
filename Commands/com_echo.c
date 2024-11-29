/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:20:41 by alfreire          #+#    #+#             */
/*   Updated: 2024/11/29 00:13:06 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	valid_flag(char *word)
{
	int	j;

	j = 1;
	while (word[j])
	{
		if (word[j] != 'n')
			return (false);
		j++;
	}
	return (true);
}

void	echo(char **words)
{
	int		i;
	bool	has_n;

	i = 0;
	has_n = false;
	while (words[i] && words[i][0] == '-')
	{
		if (!valid_flag(words[i]))
			break ;
		has_n = true;
		i++;
	}
	while (words[i])
	{
		printf("%s", words[i]);
		i++;
		if (words[i])
			printf(" ");
	}
	if (!has_n)
		printf("\n");
}
