/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/20 10:35:56 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_if_exists(char **arg, t_minish *ms)
{
	char		*path;
	struct stat	path_stat;

	path = get_executable_path(*arg, ms);
	if (!path || stat(path, &path_stat) != 0)
	{
		error("minishell: command not found\n", 127);
		exit(127);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		error("minishell: is a directory\n", 126);
		exit(126);
	}
	execve(path, arg, ms->env_list);
	error("minishell: permission denied or execution failed\n", 126);
	exit(126);
}

bool	is_builtin(char *command)
{
	return (!ft_strncmp(command, "exit", ft_strlen(command)) || \
	!ft_strncmp(command, "pwd", ft_strlen(command)) || \
	!ft_strncmp(command, "env", ft_strlen(command)) || \
	!ft_strncmp(command, "echo", ft_strlen(command)) || \
	!ft_strncmp(command, "unset", ft_strlen(command)) || \
	!ft_strncmp(command, "export", ft_strlen(command)) || \
	!ft_strncmp(command, "cd", ft_strlen(command)));
}

char	**join_cmd_arg(char	*cmd, char **args)
{
	int		i;
	int		args_count;
	char	**full_cmd;

	args_count = 0;
	while (args[args_count])
		args_count++;
	full_cmd = malloc(sizeof(char *) * (args_count + 2));
	if (!full_cmd)
		return (NULL);
	full_cmd[0] = ft_strdup(cmd);
	i = 0;
	while (i < args_count)
	{
		full_cmd[i + 1] = ft_strdup(args[i]);
		i++;
	}
	full_cmd[i + 1] = NULL;
	return (full_cmd);
}

void	do_command(char	*cmd, char **args, t_minish *ms)
{
	char	**full_cmd;

	set_exit_status(0);
	if (!is_builtin(cmd))
	{
		full_cmd = join_cmd_arg(cmd, args);
		exec_if_exists(full_cmd, ms);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	if (ft_str_cmp(cmd, "pwd"))
		printf("%s\n", ms->cwd);
	else if (ft_str_cmp(cmd, "echo"))
		echo(args);
	else if (ft_str_cmp(cmd, "exit"))
		exit_bash(args, ms);
	else if (ft_str_cmp(cmd, "env"))
		env(args, ms->env_list);
	else if (ft_str_cmp(cmd, "export"))
		ft_export(args, ms);
	else if (ft_str_cmp(cmd, "unset"))
		unset(args, ms);
	else if (ft_str_cmp(cmd, "cd"))
		cd(args, ms);
}

pid_t	child_exec(t_ast *node, t_minish *ms)
{
	pid_t	pid;

	treat_child_signal();
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: erro ao criar processo filho"); // WIP não, assim não
		return (-1);
	}
	if (pid == 0)
	{
		if (ms->fd_in == -1 || ms->fd_out == -1)
			sanitize_ms(ms, true);
		if (!is_builtin(node->cmd))
			pipe_data_flow(node->index, ms, join_cmd_arg(node->cmd, node->args));
		else
			pipe_data_flow(node->index, ms, NULL);
		relinking_in_out(ms);
		do_command(node->cmd, node->args, ms);
		sanitize_ms(ms, true);
	}
	close_in_out(node->index, ms);
	return (pid);
}

pid_t	pipeline_exec(t_ast	*node, t_minish *ms)
{
	pid_t	last_child_pid;

	last_child_pid = 0;
	if (!node)
		return (last_child_pid);
	last_child_pid = pipeline_exec(node->left, ms);
	last_child_pid = pipeline_exec(node->right, ms);
	if (!is_redir_or_pipe(node->cmd))
	{
		if (need2be_parent(node->cmd, node->args[0]))
			do_command(node->cmd, node->args, ms);
		else
			last_child_pid = child_exec(node, ms);
	}
	else if (is_redirection(node->cmd))
		execute_redir(node->cmd, node->args[0], ms);
	return (last_child_pid);
}

void	execute(t_minish *ms)
{
	int		status;
	pid_t	last;
	t_ast	*head;

	head = lastpipe(ms->cmd_list);
	status = 0x7F;
	pipeline_matrix(ms);
	last = pipeline_exec(head, ms);
	last = waitpid(last, &status, 0);
	while (waitpid(0, NULL, 0) > 0)
		continue ;
	if (WIFEXITED(status))
		set_exit_status(WEXITSTATUS(status));
	set_signals();
}
