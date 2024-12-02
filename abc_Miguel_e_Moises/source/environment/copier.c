/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copier.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:37:09 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/20 15:45:36 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**copy_environment(char **envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc((i + 1) * sizeof(char *));
	if (!new_envp)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
			delete_remaining_variables(new_envp, i);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

void	delete_remaining_variables(char **variables, int len)
{
	perror("strdup");
	while (variables[len] && len > 0)
	{
		free(variables[len]);
		len--;
	}
	free(variables);
	exit(EXIT_FAILURE);
}
