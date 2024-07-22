/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaling.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/07/22 18:00:30 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_signals(void)
{
	//struct sigaction	signal_action;
//
	//signal_action.sa_handler = &handle_interrupt;
	//signal_action.sa_flags = 0;
	//sigemptyset(&signal_action.sa_mask);
	//sigaction(SIGINT, &signal_action, NULL)
	signal(SIGINT, handle_interrupt);
	signal(SIGQUIT, SIG_IGN); //Ignora sinal de saida
}
