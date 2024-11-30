/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_aux3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:56:02 by alfreire          #+#    #+#             */
/*   Updated: 2024/11/30 16:24:12 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	pid_error(char *hd_file)
{
	perror("fork");
	free(hd_file);
	return (-1);
}

static int	report_hd_error(char *hd_file, int status)
{
	set_exit_status(status);
	free(hd_file);
	return (-1);
}

static int	fd_file(char *hd_file)
{
	int		fd;

	fd = open(hd_file, O_RDONLY);
	if (fd == -1)
		return (report_hd_error(hd_file, 130));
	free(hd_file);
	return (fd);
}

static int	heredoc(char *delimiter, t_minish *ms, bool flag)
{
	int		status;
	pid_t	pid;
	char	*hd_file;

	sig_ignore();
	hd_file = create_hd_file(ms, true, ms->hd);
	pid = fork();
	if (pid == -1)
		return (pid_error(hd_file));
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
		return (report_hd_error(hd_file, 130));
	else if (WIFEXITED(status) && WEXITSTATUS(status) == SIGINT)
		return (report_hd_error(hd_file, status));
	return (fd_file(hd_file));
}

int	do_heredoc(char *delimiter, t_minish *ms)
{
	bool	flag;

	flag = false;
	if (ft_strchr(delimiter, '"') || ft_strchr(delimiter, '\''))
		flag = true;
	ms->hd++;
	return (heredoc(delimiter, ms, flag));
}
