/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:56:02 by alfreire          #+#    #+#             */
/*   Updated: 2024/11/28 22:03:07 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	heredoc(char *delimiter, t_minish *ms, bool flag)
{
	int		status;
	pid_t	pid;
	char	*hd_file;
	int		fd;

	ms->hd++;
	sig_ignore();
	hd_file = create_hd_file(ms->hd, true);
	if (!hd_file)
		hd_sanitize(ms, 1);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(hd_file);
		return (-1);
	}
	if (pid == 0)
	{
		handle_hd_int(-1, ms, delimiter, hd_file);
		signal(SIGINT, (void *)handle_hd_int);
		signal(SIGTERM, (void *)handle_hd_int);
		read_until_deli(delimiter, ms, hd_file, flag);
		hd_sanitize(ms, 0);
	}
	waitpid(pid, &status, 0);
	set_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		set_exit_status(130);
		free(hd_file);
		return (-1);
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) == SIGINT)
	{
		set_exit_status(WEXITSTATUS(status));
		free(hd_file);
		return (-1);
	}
	fd = open(hd_file, O_RDONLY);
	if (fd == -1)
	{
		set_exit_status(130);
		free(hd_file);
		return (-1);
	}
	free(hd_file);
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

int	do_heredoc(char *delimiter, t_minish *ms)
{
	bool	flag;

	flag = false;
	if (ft_strchr(delimiter, '"') || ft_strchr(delimiter, '\''))
		flag = true;
	return (heredoc(delimiter, ms, flag));
}

void	execute_redir(const char *type, char *filename, t_minish *ms)
{
	int	fd;

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
			ms->dont_execve = true;
			return ;
		}
		if (ms->fd_in != STDIN_FILENO)
			close(ms->fd_in);
		ms->fd_in = fd;
	}
}
