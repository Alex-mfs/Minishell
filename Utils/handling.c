/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/30 16:43:04 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_interrupt(int signum)
{
	if (signum != SIGINT)
		return ;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	set_exit_status(130);
}

void	handle_child_quit(int signal)
{
	if (signal != SIGQUIT)
		return ;
	set_exit_status(130);
}

void	handle_child_interrupt(int signal)
{
	if (signal != SIGINT)
		return ;
	ft_putstr_fd("\n", 2);
	set_exit_status(131);
}

void	handle_hd_int(int signum, t_minish *ms, char *delimiter, char *hd)
{
	static t_minish		*ms_tmp;

	(void)delimiter;
	(void)hd;
	if (signum == -1)
		ms_tmp = ms;
	else if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		unlink_hd_file(ms_tmp);
		hd_sanitize(ms, 130);
	}
}
