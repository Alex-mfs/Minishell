/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:49:29 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/30 16:21:33 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_export(char **argv, t_data *ms_data)
{
	int		i;

	i = 1;
	ms_data->return_code = 0;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '='))
		{
			handle_variable(argv, ms_data, i);
			i++;
		}
		else
		{
			if (is_variable_name_ok(argv[i]) == 0)
				prepare_error("not a valid identifier", argv[i], ms_data, 1);
			i++;
		}
	}
}

void	handle_variable(char **argv, t_data *ms_data, int i)
{
	char	*name;

	name = ft_strndup(argv[i], ft_strchr(argv[i], '=') - argv[i]);
	if (is_variable_name_ok(name) == 0 || argv[i][0] == '=')
	{
		prepare_error("not a valid identifier", name, ms_data, 1);
		free(name);
		i++;
		return ;
	}
	if (find_variable(ms_data->variables, name) != -1)
		ms_data->variables = reduce_environment(ms_data->variables, \
		name, ms_data);
	ms_data->variables = \
	expand_environment(ms_data->variables, argv[i], ms_data);
	free(name);
	name = NULL;
}

void	export_helper(char *name, t_data *ms_data, int i)
{
	prepare_error("not a valid identifier", name, ms_data, 1);
	free(name);
	i++;
}

void	export_env(t_data *ms_data)
{
	char	*name;
	char	*value;
	char	**variables;
	int		i;

	i = 0;
	variables = ms_data->variables;
	while (variables[i] != NULL)
	{
		name = ft_strndup(variables[i], \
		ft_strchr(variables[i], '=') - variables[i]);
		value = ft_strchr(variables[i], '=') + 1;
		write(1, "declare -x ", 11);
		write(1, name, ft_strlen(name));
		write(1, "=\"", 2);
		write(1, value, ft_strlen(value));
		write(1, "\"\n", 2);
		free(name);
		i++;
	}
	ms_data->return_code = 0;
}
