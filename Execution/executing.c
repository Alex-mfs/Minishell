/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/12/02 09:08:48 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_if_exists(char **arg, t_minish *ms, t_ast *node)
{
	char		*path;
	struct stat	path_stat;
	char		*str;
	//char		**tmp;
	//char buf[1024]; //JOAO

	path = get_executable_path(*arg, ms);
	if (!path || stat(path, &path_stat) != 0)
	{
		str = which_error("", *arg, ": command not found\n");
		ft_putstr_fd(str, 2);
		free(str);
		set_exit_status(127);
		ft_free_matrix(arg);
		sanitize_ms(ms, true);
	}
	if (S_ISDIR(path_stat.st_mode))
		deal_with_isdir(ms, arg, path);
	/*//JOAO
	printf("PID=%d, Reading from fd_in\n", getpid());
	while (read(STDIN_FILENO, buf, sizeof(buf)) > 0) {
	    write(STDOUT_FILENO, buf, sizeof(buf));
	}
	printf("PID=%d, EOF detected\n", getpid());
	//JOAO*/
	/*i = 0;
	while (i < 2)
	{
		ft_putnbr_fd(ms->pipes[i][0], 2);
		ft_putnbr_fd(ms->pipes[i][1], 2);
		i++;
	}*/
	//tmp = ft_matrix_dup(ms->env_list);
	//if (ft_str_cmp(arg[0], "cat") && (!arg[1] || !arg[1][0]) && node->next && node->next->index < 0)
	//	close(ms->pipes[node->index][0]);
	node->empty_quotes = false;
	execve(path, arg, ms->env_list);
	error("minishell: permission denied or execution failed\n", 126);
	sanitize_ms(ms, true);
}

void	do_command(t_ast *node, t_minish *ms)
{
	char	**full_cmd;
	int		tmp;

	tmp = get_exit_status();
	set_exit_status(0);
	if (!is_builtin(node->cmd))
	{
		if (ms->dont_execve)
			return ;
		full_cmd = join_cmd_arg(node->cmd, node->args);
		exec_if_exists(full_cmd, ms, node);
		error_execve(ms);
	}
	if (ft_str_cmp(node->cmd, "pwd"))
		printf("%s\n", ms->cwd);
	else if (ft_str_cmp(node->cmd, "echo"))
		echo(node->args);
	else if (ft_str_cmp(node->cmd, "exit"))
		exit_bash(node->args, ms, tmp);
	else if (ft_str_cmp(node->cmd, "env"))
		env(node->args, ms->env_list);
	else if (ft_str_cmp(node->cmd, "export"))
		ft_export(node->args, ms);
	else if (ft_str_cmp(node->cmd, "unset"))
		unset(node->args, ms);
	else if (ft_str_cmp(node->cmd, "cd"))
		cd(node->args, ms);
}

pid_t	child_exec(t_ast *node, t_minish *ms)
{
	pid_t	pid;

	treat_child_signal();
	/*//JOAO
	for (int i = 0; i < 1024; i++) {
    	if (fcntl(i, F_GETFD) != -1) {
        	printf("PID=%d, Open FD: %d\n", getpid(), i);
	    }
	}// JOAO*/
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: Error while creating child process");
		return (-1);
	}
	if (pid == 0)
	{
		if (ms->fd_in == -1 || ms->fd_out == -1)
			sanitize_ms(ms, true);
		pipe_data_flow(node->index, ms);
		relinking_in_out(ms);
		do_command(node, ms);
		sanitize_ms(ms, true);
	}
	close_in_out(node->index, ms);
	//waitpid(pid, NULL, 0);
	return (pid);
}

pid_t	pipeline_exec(t_ast *node, t_minish *ms)
{
	pid_t	last_child_pid;
	bool	redir_error;

	last_child_pid = 0;
	redir_error = false;
	if (node == NULL)
		return (last_child_pid);
	last_child_pid = pipeline_exec(node->left, ms);
	if (ms->dont_execve)
		return (last_child_pid);
	last_child_pid = pipeline_exec(node->right, ms);
	if (!is_redir_or_pipe(node->cmd))
	{
		redir_error = process_redirections(node, ms);
		if (redir_error || ms->dont_execve)
			return (last_child_pid);
		if (need2be_parent(node->cmd, node->args[0], ms))
			do_command(node, ms);
		else
			last_child_pid = child_exec(node, ms);
	}
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
