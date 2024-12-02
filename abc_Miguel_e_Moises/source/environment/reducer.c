/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reducer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:47:23 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/25 16:07:05 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**reduce_environment(char **envp, char *var, t_data *ms_data)
{
	char	**new_envp;
	int		index;
	int		len;

	index = find_variable(envp, var);
	if (index == -1)
	{
		return (envp);
	}
	len = 0;
	while (envp[len])
		len++;
	new_envp = malloc((len) * sizeof(char *));
	if (!new_envp)
	{
		prepare_error("Malloc failed", var, ms_data, 1);
		return (NULL);
	}
	if (reducer_helper(envp, new_envp, ms_data, index) == 1)
		return (NULL);
	delete_variables(envp);
	ms_data->return_code = 0;
	return (new_envp);
}

int	reducer_helper(char **envp, char **new_envp, t_data *ms_data, int index)
{
	int		j;
	int		i;
	int		len;

	(void)ms_data;
	j = 0;
	i = 0;
	len = 0;
	while (envp[len])
		len++;
	while (i < (len))
	{
		if (i != index)
		{
			new_envp[j] = ft_strdup(envp[i]);
			if (!new_envp[j])
				return (delete_remain_reducer(new_envp, j, ms_data));
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	return (0);
}

int	delete_remain_reducer(char **variables, int len, t_data *ms_data)
{
	perror("strdup");
	while (len > 0 && variables[len])
	{
		free(variables[len]);
		len--;
	}
	free(variables);
	ms_data->return_code = 1;
	return (1);
}
