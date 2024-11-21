/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:56:02 by alfreire          #+#    #+#             */
/*   Updated: 2024/11/21 17:22:57 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	heredoc(char *delimiter, t_minish *ms)
{
	int		fd;
	int		status;
	pid_t	pid;

	set_signals_heredoc();
	if (ms->fd_in > STDIN_FILENO)
		close(ms->fd_in);
	pid = fork();
	if (pid == 0)
	{
		set_signals_heredoc();
		read_until_delimiter(delimiter, ms);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		set_exit_status(130);
		return (-1);
	}
	set_signals();
	fd = open("heredoc_tmp", O_RDONLY);
	if (fd == -1)
		error("minishell: heredoc\n", 1);
	return (fd);
}

static int	do_heredoc(t_minish *ms, char *filename)
{
	int	fd_ret;

	fd_ret = heredoc(filename, ms);
	if (fd_ret == -1)
		set_exit_status(1);
	if (fd_ret == -1 && fd_ret != STDIN_FILENO)
		close(fd_ret);
	if (fd_ret != -1)
		dup2(ms->fd_in, fd_ret);
	return (fd_ret);
}

void	execute_redir(const char *type, char *filename, t_minish *ms)
{
	int	local_fd_in;
	int	local_fd_out;

	local_fd_in = ms->fd_in;
	local_fd_out = ms->fd_out;
	if (type[0] == '>')
	{
		if (type[1] == '>')
			local_fd_out = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else
			local_fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (local_fd_out == -1)
		{
			perror(filename);
			set_exit_status(1);
			return ;
		}
		//if (local_fd_out != STDOUT_FILENO)
		//	close(local_fd_out);
		ms->fd_out = local_fd_out;
	}
	else if (ft_str_cmp(type, "<"))
	{
		local_fd_in = open(filename, O_RDONLY);
		if (local_fd_in == -1)
		{
			perror(filename);
			set_exit_status(1);
			return ;
		}
		//if (local_fd_in != STDIN_FILENO)
		//	close(local_fd_in);
		ms->fd_in = local_fd_in;
	}
	else if (ft_str_cmp(type, "<<"))
		local_fd_in = do_heredoc(ms, filename);
}
