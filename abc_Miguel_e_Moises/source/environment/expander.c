/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:47:28 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/30 16:22:00 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	initial_checks_expander(char **envp, char *var, t_data *ms_data)
{
	if (!var)
	{
		prepare_error("Variable is NULL. Malloc related", \
		"expand_environment", ms_data, 1);
		return (1);
	}
	if (!envp)
	{
		prepare_error("Environment is NULL. Malloc related", \
		"expand_environment", ms_data, 1);
		return (1);
	}
	return (0);
}

int	expander_helper(char **envp, char **new_envp, char *var, t_data *ms_data)
{
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			prepare_error("ft_strdup failed. Malloc related", var, ms_data, 1);
			return (delete_remain_expander(new_envp, i));
		}
		i++;
	}
	delete_variables(envp);
	new_envp[i] = ft_strdup(var);
	if (!new_envp[i])
	{
		prepare_error("ft_strdup failed. Malloc related", var, ms_data, 1);
		return (1);
	}
	i++;
	new_envp[i] = NULL;
	return (0);
}

int	delete_remain_expander(char **variables, int len)
{
	while (len > 0 && variables[len])
	{
		free(variables[len]);
		len--;
	}
	free(variables);
	return (1);
}

char	**expand_environment(char **envp, char *var, t_data *ms_data)
{
	char	**new_envp;
	int		i;

	i = 0;
	if (initial_checks_expander(envp, var, ms_data) == 1)
	{
		return (NULL);
	}
	while (envp[i])
		i++;
	new_envp = malloc((i + 2) * sizeof(char *));
	if (!new_envp)
	{
		prepare_error("Malloc failed", "expand_environment", ms_data, 1);
		return (NULL);
	}
	if (expander_helper(envp, new_envp, var, ms_data) == 1)
	{
		return (NULL);
	}
	return (new_envp);
}
