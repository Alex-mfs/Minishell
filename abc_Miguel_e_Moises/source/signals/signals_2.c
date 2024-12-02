/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:56:47 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/30 17:00:23 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_eof(int sig)
{
	(void)sig;
	g_sig_num = S_SIGEOF;
}

void	signal_child(int sig)
{
	(void)sig;
	g_sig_num = S_SIGINT;
	exit(130);
}

void	ignore_child(int sig)
{
	if (sig == 2)
	{
		write(1, "\n", 1);
		g_sig_num = S_SIGQUIT;
	}
	else if (sig == 3)
	{
		write(1, "Quit (core dumped)\n", 20);
		g_sig_num = S_SIGINT;
	}
}

void	update_codes_130(t_data *ms_data, int *return_code)
{
	ms_data->return_code = 130;
	*return_code = 130;
	g_sig_num = NO_SIG;
}

void	handle_signals(t_data *ms_data)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	(void)ms_data;
	signal(SIGQUIT, SIG_IGN);
}
