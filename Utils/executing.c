/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/10/19 19:05:09 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_if_btin_exists(char *cmd, char **arg, t_minish *ms)
{
	char		*path;
	struct stat	path_stat;

	path = get_executable_path(cmd, ms);
	if (path && stat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
			error("minishell: is a directory\n", 126);
		else if (S_ISREG(path_stat.st_mode))
		{
			execve(path, arg, ms->env_list);
			error("minishell: permission denied or execution failed\n", 126);
		}
		ft_free(path);
	}
	else
		error("minishell: command not found\n", 127);
}

void	do_command(char	*cmd, char **args, t_minish *ms)
{
	set_exit_status(0);
	if (ft_str_cmp(cmd, "pwd"))
		printf("%s\n", ms->cwd);
	else if (ft_str_cmp(cmd, "echo"))
		echo(args);
	else if (ft_str_cmp(cmd, "exit"))
		exit_bash(args);
	else if (ft_str_cmp(cmd, "env"))
		env(args, ms->env_list);
	else if (ft_str_cmp(cmd, "export"))
		export(args, ms);
	else if (ft_str_cmp(cmd, "unset"))
		unset(args, ms);
	else if (ft_str_cmp(cmd, "cd"))
		cd(args, ms);
	else
		execute_if_btin_exists(cmd, args, ms);
}

pid_t	child_exec(t_ast *node, t_minish *ms)
{
	pid_t	pid;

	treat_child_signal();
	pid = fork();
	if (pid == 0)
	{
		if (ms->fd_in == -1 || ms->fd_out == -1)
			sanitize(true);
		pipe_data_flow(node->index, ms);
		relinking_in_out(ms);
		do_command(node->cmd, node->args, ms);
		sanitize(true);
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
	if (!is_redir_or_pipe(node->token))
	{
		if (need2be_parent(node->cmd, node->args[0]))
			do_command(node->cmd, node->args, ms);
		else
			last_child_pid = child_exec(node, ms);
	}
	else if (is_redirection(node->token))
		execute_redirection(node->token->type, node->args[0], ms);
	return (last_child_pid);
}

void	execute(t_minish *ms, t_ast	*ast)
{
	int		status;
	pid_t	last_child_pid;

	status = 0x7F;
	pipeline_matrix(ms);
	last_child_pid = pipeline_exec(ast, ms);
	last_child_pid = waitpid(last_child_pid, &status, 0);
	while (waitpid(0, NULL, 0) > 0)
		continue ;
	if (WIFEXITED(status))
		set_exit_status(WEXITSTATUS(status));
	set_signals();
}
