/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:49:12 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/28 11:51:43 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	search_builtin(char *command)
{
	if (!ft_strcmp(command, "echo"))
		return (true);
	if (!ft_strcmp(command, "pwd"))
		return (true);
	if (!ft_strcmp(command, "export"))
		return (true);
	if (!ft_strcmp(command, "unset"))
		return (true);
	if (!ft_strcmp(command, "env"))
		return (true);
	if (!ft_strcmp(command, "exit"))
		return (true);
	if (!ft_strcmp(command, "cd"))
		return (true);
	return (false);
}

void	ft_exec_builtin(char **argv, t_data *ms_data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		prepare_error("getcwd failed", "in ft_exec_builtin", ms_data, 1);
		return ;
	}
	if (check_options_built_ins(argv, ms_data) == 1)
	{
		free(pwd);
		return ;
	}
	else
	{
		ft_exec_builtin_2(argv, ms_data, pwd);
		return ;
	}
	free(pwd);
}

void	ft_exec_builtin_2(char **argv, t_data *ms_data, char *pwd)
{
	if (strcmp(argv[0], "unset") == 0)
	{
		handle_unset(argv, ms_data);
		free(pwd);
		return ;
	}
	else if (strcmp(argv[0], "env") == 0)
		handle_env(argv, ms_data);
	else if (strcmp(argv[0], "exit") == 0)
		handle_exit(argv, ms_data, pwd);
	else if (strcmp(argv[0], "pwd") == 0)
		handle_pwd(argv, ms_data);
	else if (strcmp(argv[0], "echo") == 0)
	{
		handle_echo(argv);
		ms_data->return_code = 0;
	}
	else
	{
		ft_exec_builtin_3(argv, ms_data, pwd);
		return ;
	}
	free(pwd);
}

void	ft_exec_builtin_3(char **argv, t_data *ms_data, char *pwd)
{
	if (strcmp(argv[0], "export") == 0)
	{
		if (argv[1] == NULL)
		{
			export_env(ms_data);
			free(pwd);
			return ;
		}
		handle_export(argv, ms_data);
		free(pwd);
		return ;
	}
	else if (strcmp(argv[0], "cd") == 0)
	{
		handle_cd(ms_data, argv, pwd);
		return ;
	}
}
