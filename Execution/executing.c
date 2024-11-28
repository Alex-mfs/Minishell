/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/28 21:03:32 by joao-rib         ###   ########.fr       */
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
		printf("minishell: %s: command not found\n", *arg);
		set_exit_status(127);
		ft_free_matrix(arg);
		sanitize_ms(ms, true);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_free_matrix(arg);
		error("minishell: is a directory\n", 126);
		sanitize_ms(ms, true);
	}
	execve(path, arg, ms->env_list);
	error("minishell: permission denied or execution failed\n", 126);
	sanitize_ms(ms, true);
}

void	do_command(char	*cmd, char **args, t_minish *ms)
{
	char	**full_cmd;

	set_exit_status(0);
	if (!is_builtin(cmd))
	{
		if (ms->dont_execve)
			return ;
		full_cmd = join_cmd_arg(cmd, args);
		exec_if_exists(full_cmd, ms);
		error_execve(ms);
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

	printf("Test child exec, cmd=%s, bool=%d\n", node->cmd, (int)node->empty_quotes);
	treat_child_signal();
	pid = fork();
	printf("Test child exec, cmd=%s, bool=%d\n", node->cmd, (int)node->empty_quotes);
	if (pid == -1)
	{
		perror("minishell: Error while creating child process");
		return (-1);
	}
	if (pid == 0)
	{
		if (ms->fd_in == -1 || ms->fd_out == -1)
			sanitize_ms(ms, true);
		if (!is_builtin(node->cmd))
			create_fullcmd_pipe_flow(ms, node);
		else
			pipe_data_flow(node->index, ms, NULL);
		relinking_in_out(ms);
		printf("Test child exec, cmd=%s, bool=%d\n", node->cmd, (int)node->empty_quotes);
		do_command(node->cmd, node->args, ms);
		sanitize_ms(ms, true);
	}
	close_in_out(node->index, ms);
	return (pid);
}

// pid_t	pipeline_exec(t_ast	*node, t_minish *ms)
// {
// 	pid_t	last_child_pid;
// 	t_ast	*redir_node;

// 	last_child_pid = 0;
// 	if (!node)
// 		return (last_child_pid);
// 	ms->dont_execve = false;
// 	last_child_pid = pipeline_exec(node->left, ms);
// 	last_child_pid = pipeline_exec(node->right, ms);
// 	if (!is_redir_or_pipe(node->cmd))
// 	{
// 		redir_node = node->redirections;
// 		while (redir_node)
// 		{
// 			execute_redir(redir_node->cmd, redir_node->args[0], ms);
// 			redir_node = redir_node->next;		
// 		}
// 		if (need2be_parent(node->cmd, node->args[0], ms))
// 			do_command(node->cmd, node->args, ms);
// 		else
// 			last_child_pid = child_exec(node, ms);
// 	}
// 	else if (is_redirection(node->cmd))
// 		execute_redir(node->cmd, node->args[0], ms);
// 	return (last_child_pid);
// }

bool is_input_redirection(const char *type)
{
    return (ft_str_cmp(type, "<") || ft_str_cmp(type, "<<"));
}

bool is_output_redirection(const char *type)
{
    return (ft_str_cmp(type, ">") || ft_str_cmp(type, ">>"));
}

bool process_out_redirections(t_ast *node, t_minish *ms)
{
	t_ast *redir_node;
	bool redir_error;

	redir_error = false;
	redir_node = node->redirections;
	while (redir_node != NULL)
	{
		if (is_output_redirection(redir_node->cmd))
		{
			execute_redir(redir_node->cmd, redir_node->args[0], ms);
			if (ms->dont_execve)
			{
				redir_error = true;
				break;
			}
		}
		redir_node = redir_node->next;
	}

	return (redir_error);
}

bool process_redirections(t_ast *node, t_minish *ms)
{
    t_ast *redir_node;
    bool redir_error;
    
    redir_error = false;
    redir_node = node->redirections;
    while (redir_node != NULL)
    {
        if (is_input_redirection(redir_node->cmd))
        {
            execute_redir(redir_node->cmd, redir_node->args[0], ms);
            if (ms->dont_execve)
            {
                redir_error = true;
                break;
            }
        }
        redir_node = redir_node->next;
    }
    if (redir_error)
        return (redir_error);
	else
		redir_error = process_out_redirections(node, ms);
    return (redir_error);
}

pid_t pipeline_exec(t_ast *node, t_minish *ms)
{
	pid_t	last_child_pid;
	bool	redir_error;

	last_child_pid = 0;
	redir_error = false;
	if (node == NULL)
		return last_child_pid;
	ms->dont_execve = false;
	last_child_pid = pipeline_exec(node->left, ms);
	last_child_pid = pipeline_exec(node->right, ms);
	if (!is_redir_or_pipe(node->cmd))
	{
		redir_error = process_redirections(node, ms);
		if (redir_error || ms->dont_execve)
			return (last_child_pid);
		if (need2be_parent(node->cmd, node->args[0], ms))
			do_command(node->cmd, node->args, ms);
		else
			last_child_pid = child_exec(node, ms);
	}
	else if (is_redirection(node->cmd))
		execute_redir(node->cmd, node->args[0], ms);
	return (last_child_pid);
}

// void	execute(t_minish *ms)
// {
// 	int		status;
// 	pid_t	last;
// 	t_ast	*head;

// 	head = lastpipe(ms->cmd_list);
// 	status = 0x7F;		  dessa forma nao verifica codigo de saida da child
// 	pipeline_matrix(ms);
// 	last = pipeline_exec(head, ms);
// 	last = waitpid(last, &status, 0);
// 	while (waitpid(0, NULL, 0) > 0)
// 		continue ;
// 	if (WIFEXITED(status))
// 		set_exit_status(WEXITSTATUS(status));
// 	set_signals();
// }

void	execute(t_minish *ms)
{
	int		status;
	pid_t	last;
	t_ast	*head;

	head = lastpipe(ms->cmd_list);
	status = 0x7F;
	pipeline_matrix(ms);
	last = pipeline_exec(head, ms);
	if (last > 0)
	{
		waitpid(last, &status, 0);
		while (waitpid(0, NULL, 0) > 0)
			continue ;
		if (WIFEXITED(status))
			set_exit_status(WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			set_exit_status(128 + WTERMSIG(status));
	}
	set_signals();
}