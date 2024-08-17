/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/07/29 17:43:52 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*void	pipeline_create(void)
{
	int	i;

	(ms()->pipes) = ft_calloc(ms()->num_commands, sizeof(int *));
	if (!ms()->pipes)
		return ;
	i = -1;
	while (++i < ms()->num_commands - 1)
	{
		(ms()->pipes[i]) = ft_calloc(2, sizeof(int));
		pipe(ms()->pipes[i]);
	}
}

void	pipeline_apply(int command_index)
{
	if (ms()->num_commands < 2)
		return ;
	if (ms()->in_fd == STDIN_FILENO)
		if (command_index != 0)
			ms()->in_fd = ms()->pipes[command_index - 1][READ_END];
	if (ms()->out_fd == STDOUT_FILENO)
		if (!is_last_command(command_index))
			ms()->out_fd = ms()->pipes[command_index][WRITE_END];
}

bool	is_last_command(int command_index)
{
	return (command_index == ms()->num_commands - 1);
}

bool	is_unforkable(char *command, char *arg)
{
	return (!ft_strcmp(command, "cd") || !ft_strcmp(command, "exit") \
		|| (!ft_strcmp(command, "export") && arg) || !ft_strcmp(command, "unset") \
		|| !ft_strcmp(command, "ptmp"));
}

bool	is_builtin(char *command)
{
	return (!ft_strcmp(command, "exit") || !ft_strcmp(command, "pwd") \
		|| !ft_strcmp(command, "env") || !ft_strcmp(command, "echo") \
		|| !ft_strcmp(command, "unset") || !ft_strcmp(command, "export") \
		|| !ft_strcmp(command, "cd") || !ft_strcmp(command, "ptmp"));
}

void	_execute_if_exists(char *exe, char **argv)
{
	char		*path;
	struct stat	path_stat;

	path = get_executable_path(exe);
	stat(path, &path_stat);
	if (path)
	{
		if (S_ISDIR(path_stat.st_mode))
			error(ANSI_RED, ERROR_DIRECTORY, path, 126);
		else if (S_ISREG(path_stat.st_mode))
		{
			execve(path, argv, ms()->envp);
			error(ANSI_RED, ERROR_NO_PERMISSIONS, exe, 126);
		}
		ft_free(path);
	}
	else
		error(ANSI_RED, ERROR_UNKNOWN_CMD, exe, 127);
	return ;
}

void	_execute_command(char **args)
{
	(ms()->exit_status) = 0;
	if (!is_builtin(args[0]))
		_execute_if_exists(args[0], args);
	else if (!ft_strcmp(args[0], "exit"))
		ft_exit(args + 1);
	else if (!ft_strcmp(args[0], "pwd"))
		printf("%s\n", ms()->cwd);
	else if (!ft_strcmp(args[0], "env"))
		ft_env(args + 1);
	else if (!ft_strcmp(args[0], "echo"))
		ft_echo(args + 1);
	else if (!ft_strcmp(args[0], "unset"))
		ft_unset(args + 1);
	else if (!ft_strcmp(args[0], "export"))
		ft_export(args + 1);
	else if (!ft_strcmp(args[0], "cd"))
		ft_cd(args + 1);
	else if (!ft_strcmp(args[0], "ptmp"))
		tmp_debug();
}

pid_t	_execute_forkable(t_ast *command)
{
	pid_t	pid;

	signals_child();
	pid = fork();
	if (pid == 0)
	{
		if (ms()->in_fd == -1 || ms()->out_fd == -1)
			sanitize(true);
		pipeline_apply(command->index);
		io_connect();
		_execute_command(command->args);
		sanitize(true);
	}
	io_disconnect(command->index);
	return (pid);
}

pid_t	_execute_pipeline(t_ast *node)
{
	pid_t	last;

	last = 0;
	if (!node)
		return (last);
	last = _execute_pipeline(node->left);
	last = _execute_pipeline(node->right);
	if (!is_redir_or_pipe(node->token))
	{
		if (is_unforkable(node->args[0], node->args[1]))
			_execute_command(node->args);
		else
			last = _execute_forkable(node);
	}
	else if (is_redirection(node->token))
		execute_redirection(node->token->type, node->args[0]);
	return (last);
}*/

void	execute(t_minish *ms)
{
/*	int		status;
	pid_t	last;

	status = 0x7F;
	pipeline_create();
	last = _execute_pipeline(ast);
	last = waitpid(last, &status, 0);
	while (waitpid(0, NULL, 0) > 0)
		continue ;
	if (WIFEXITED(status))
		ms()->exit_status = WEXITSTATUS(status);
	signals();*/

	int		status;
	pid_t	child_pid;

	//status = 0x7F; "=127"
	//criar um int** onde regista comandos, de alguma forma
	//WIP executar pipeline, gravar pid (criado com fork()?) respectivo em "child_pid"
	//WIP child_pid = waitpid(child_pid, &status, 0);
	//WIP esperar até terminarem todos os child processes antes de continuar o programa
	//WIP se o processo terminar normalmente, gravar o seu exit_status
	//WIP ?signals()?
}
