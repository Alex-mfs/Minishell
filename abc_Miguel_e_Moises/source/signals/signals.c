/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:26:31 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/30 17:05:10 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_heredoc(int sig, t_data *ms_data, char *delimiter, int fd)
{
	static t_data	*ms_data_tmp;
	static char		*delimiter_tmp;
	static int		fd_tmp;

	if (sig == -1)
	{
		ms_data_tmp = ms_data;
		delimiter_tmp = delimiter;
		fd_tmp = fd;
	}
	else if (sig == SIGINT)
	{
		g_sig_num = S_SIGINT;
		write(1, "\n", 1);
		exit_heredoc(ms_data_tmp, delimiter_tmp, fd_tmp, SIG_INT_TERM);
	}
}

void	handle_sigint(int sig, siginfo_t *info, void *context)
{
	t_data	*ms_data;

	(void)sig;
	(void)info;
	g_sig_num = S_SIGINT;
	ms_data = (t_data *)context;
	if (ms_data)
	{
		ms_data->return_code = 130;
	}
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	exit_child(t_data *ms_data, int exit_code)
{
	if (ms_data)
		clean_shell(ms_data);
	exit(exit_code);
}

void	signal_child_handler(int sig, t_data *ms_data, int parent_pid)
{
	static t_data		*ms_data_tmp;
	static int			sig_tmp;
	static int			parent_pid_tmp;

	(void)parent_pid_tmp;
	if (sig == -1)
	{
		ms_data_tmp = ms_data;
		parent_pid_tmp = parent_pid;
		sig_tmp = 0;
	}
	else if (sig == SIGINT)
	{
		g_sig_num = S_SIGINT;
		if (sig_tmp == 0)
		{
			kill(parent_pid, 2);
			sig_tmp = 1;
		}
		exit_child(ms_data_tmp, SIG_INT_TERM);
	}
	else if (sig == SIGQUIT)
		case_sigquit(parent_pid, ms_data, sig_tmp, ms_data_tmp);
}

void	case_sigquit(int parent_pid, t_data *ms_data, int sig_tmp, \
t_data *ms_data_tmp)
{
	(void)ms_data;
	g_sig_num = S_SIGQUIT;
	if (sig_tmp == 0)
	{
		kill(parent_pid, 3);
		sig_tmp = 1;
	}
	exit_child(ms_data_tmp, 131);
}
