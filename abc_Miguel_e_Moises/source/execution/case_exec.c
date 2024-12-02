/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:49:12 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/28 16:56:28 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	case_exec(t_exec *exec_cmd, t_data *ms_data)
{
	char	*executable;
	int		exit_code;

	exit_code = 0;
	if (exec_cmd->argv[0][0] == '\0')
	{
		clean_shell(ms_data);
		exit(exit_code);
	}
	if (search_builtin(exec_cmd->argv[0]))
	{
		ft_exec_builtin(exec_cmd->argv, ms_data);
		exit_code = ms_data->return_code;
		clean_shell(ms_data);
		exit(exit_code);
	}
	executable = get_executable_path(exec_cmd, ms_data);
	if (executable)
		handle_executable(executable, exec_cmd, ms_data);
	else
		ft_cmd_not_found_error(exec_cmd->argv[0], ms_data, exit_code);
}

char	*get_executable_path(t_exec *exec_cmd, t_data *ms_data)
{
	if (exec_cmd->argv[0][0] == '.' || exec_cmd->argv[0][0] == '/')
	{
		return (ft_strdup(exec_cmd->argv[0]));
	}
	else
	{
		return (find_executable(exec_cmd->argv[0], ms_data));
	}
}

void	handle_executable(char *executable, t_exec *exec_cmd, t_data *ms_data)
{
	struct stat	file_stat;
	int			exit_code;

	if (stat(executable, &file_stat) == 0 && S_ISDIR(file_stat.st_mode))
	{
		print_exec_error("Is a directory", executable);
		exit_code = 126;
		free(executable);
		clean_shell(ms_data);
		exit(exit_code);
	}
	execve(executable, exec_cmd->argv, ms_data->variables);
	handle_exec_errors(executable, ms_data);
	exit_code = ms_data->return_code;
	free(executable);
	clean_shell(ms_data);
	exit(exit_code);
}

void	ft_cmd_not_found_error(char *command, t_data *ms_data, int exit_code)
{
	prepare_error("command not found", command, ms_data, 127);
	exit_code = ms_data->return_code;
	clean_shell(ms_data);
	exit(exit_code);
}
