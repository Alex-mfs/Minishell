/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:32:44 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/30 16:22:19 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*my_getenv_expans(char *var_name, char **variables)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var_name);
	while (variables[i])
	{
		if (ft_strncmp(variables[i], var_name, len) == 0 && \
		variables[i][len] == '=')
			return (variables[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*my_getenv(char *var_name, char **variables)
{
	int		i;
	int		len;
	char	*var_value;

	i = 0;
	len = ft_strlen(var_name);
	while (variables[i])
	{
		if (ft_strncmp(variables[i], var_name, len) == 0 && \
		variables[i][len] == '=')
		{
			var_value = ft_strdup(variables[i] + len + 1);
			if (!var_value)
			{
				perror("strdup");
				exit(EXIT_FAILURE);
			}
			return (var_value);
		}
		i++;
	}
	return (NULL);
}

int	find_variable(char **envp, const char *name)
{
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

int	is_variable_name_ok(char *name)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[0]) || name[0] == '=')
		return (0);
	while (name[i])
	{
		if (ft_isalnum(name[i]) == 0 && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
