/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:56:02 by alfreire          #+#    #+#             */
/*   Updated: 2024/11/28 22:59:18 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

static int	exec_redir_in(t_minish *ms, const char *type, char *filename)
{
	int	fd;

	if (type[1] == '>')
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		report_error(filename, ms);
	if (ms->fd_out != STDOUT_FILENO)
		close(ms->fd_out);
	return (fd);
}

void	execute_redir(const char *type, char *filename, t_minish *ms)
{
	int	fd;

	if (type[0] == '>')
		ms->fd_out = exec_redir_in(ms, type, filename);
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
