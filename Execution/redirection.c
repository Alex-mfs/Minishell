/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:56:02 by alfreire          #+#    #+#             */
/*   Updated: 2024/11/27 11:33:31 by joao-rib         ###   ########.fr       */
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

static void	report_error(char *filename, t_minish *ms)
{
	ms->dont_execve = true;
	if (get_exit_status() != 130)
	{
		if (errno != 0)
			perror(filename);
		else
			error(filename, 2);
		set_exit_status(1);
	}
	return ;
}

int	do_heredoc(const char *delimiter, t_minish *ms)
{
	int		fd;
	int		status;
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, handle_heredoc_interrupt);
		signal(SIGQUIT, SIG_DFL);
		read_until_delimiter(delimiter, ms);
		exit(0);
	}
	waitpid(pid, &status, 0);
	set_signals();
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		set_exit_status(130);
		return (-1);
	}
	fd = open("heredoc_tmp", O_RDONLY);
	if (fd == -1)
		error("minishell: heredoc\n", 1);
	return (fd);
}

void    execute_redir(const char *type, char *filename, t_minish *ms)
{
    int fd;

    if (type[0] == '>')
    {
        if (type[1] == '>')
            fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
        else
            fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (fd == -1)
            return (report_error(filename, ms));
        if (ms->fd_out != STDOUT_FILENO)
            close(ms->fd_out);
        ms->fd_out = fd;
    }
    else if (ft_str_cmp(type, "<"))
    {
        fd = open(filename, O_RDONLY);
        if (fd == -1)
            return (report_error(filename, ms));
        if (ms->fd_in != STDIN_FILENO)
            close(ms->fd_in);
        ms->fd_in = fd;
    }
    else if (ft_str_cmp(type, "<<"))
    {
        fd = do_heredoc(filename, ms);
        if (fd == -1)
		{
			if (get_exit_status() != 130)
			{
				errno = EINTR;
            	return (report_error(filename, ms));
			}
			else
			{
				ms->dont_execve = true;
				return ;
			}
		}
        if (ms->fd_in != STDIN_FILENO)
            close(ms->fd_in);
        ms->fd_in = fd;
    }
}
