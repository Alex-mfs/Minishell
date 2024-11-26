/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaling.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/05 11:04:39 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_signals(void)
{
	/*struct sigaction	signal_action;

	signal_action.sa_handler = &handle_interrupt;
	signal_action.sa_flags = 0;
	sigemptyset(&signal_action.sa_mask);
	sigaction(SIGINT, &signal_action, NULL);*/
	signal(SIGINT, handle_interrupt);
	signal(SIGQUIT, SIG_IGN); //Ignora sinal de saida?
}

void	set_signals_heredoc(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handle_heredoc_interrupt;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	treat_child_signal(void)
{
	signal(SIGQUIT, handle_child_quit); //lida com o uso de ctrl + \ durante um processo child, testar sleep 10 e ctrl '\'
	signal(SIGINT, handle_child_interrupt);
}
