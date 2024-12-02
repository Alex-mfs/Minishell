/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:02:22 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/30 16:43:52 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	case_pipe(t_pipe *pipe_cmd, t_data *ms_data)
{
	int		pipe_fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status_left;
	int		status_right;

	status_left = 0;
	status_right = 0;
	if (pipe(pipe_fd) == -1)
		prepare_pipe_error(strerror(errno), ms_data, 0);
	pid_left = fork();
	if (pid_left == -1)
		prepare_pipe_error(strerror(errno), ms_data, 1);
	if (pid_left == 0)
		setup_pipe_exec_left(pipe_cmd, ms_data, pipe_fd, pid_left);
	pid_right = fork();
	if (pid_right == -1)
		prepare_pipe_error(strerror(errno), ms_data, 1);
	if (pid_right == 0)
		setup_pipe_exec_right(pipe_cmd, ms_data, pipe_fd, pid_right);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid_left, &status_left, 0);
	waitpid(pid_right, &status_right, 0);
	end_this(status_right, ms_data);
}

void	prepare_pipe_error(char *error, t_data *ms_data, int error_code)
{
	if (error_code == 0)
		print_exec_error(error, "pipe");
	else
		print_exec_error(error, "fork");
	clean_shell(ms_data);
	exit(1);
}

void	setup_pipe_exec_left(t_pipe *pipe_cmd, t_data *ms_data, \
int *pipe_fd, pid_t pid)
{
	int	exit_code;

	(void)pid;
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		print_exec_error(strerror(errno), "dup2");
		clean_shell(ms_data);
		exit(1);
	}
	close(pipe_fd[1]);
	exec_tree(pipe_cmd->left, ms_data);
	exit_code = ms_data->return_code;
	clean_shell(ms_data);
	exit(exit_code);
}

void	setup_pipe_exec_right(t_pipe *pipe_cmd, t_data *ms_data, \
int *pipe_fd, pid_t pid)
{
	int	exit_code;

	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		print_exec_error(strerror(errno), "dup2");
		clean_shell(ms_data);
		exit(1);
	}
	close(pipe_fd[0]);
	waitpid(pid, NULL, 0);
	exec_tree(pipe_cmd->right, ms_data);
	exit_code = ms_data->return_code;
	clean_shell(ms_data);
	exit(exit_code);
}

void	end_this(int status_right, t_data *ms_data)
{
	int	exit_code;

	(void)exit_code;
	exit_code = 0;
	if (WIFEXITED(status_right))
		exit_code = WEXITSTATUS(status_right);
	else if (WIFSIGNALED(status_right))
		exit_code = WTERMSIG(status_right) + 128;
	else
		exit_code = ms_data->return_code;
	clean_shell(ms_data);
	exit(exit_code);
}
