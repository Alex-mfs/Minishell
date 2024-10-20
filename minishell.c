/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:52:25 by joao-rib          #+#    #+#             */
/*   Updated: 2024/09/25 19:14:53 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static int	g_exit_status = 0;

void	set_exit_status(int status)
{
	g_exit_status = status;
}

int	get_exit_status(void)
{
	return (g_exit_status);
}

int main(int argc, char **argv, char **envp)
{
    t_minish    ms;

    (void)argc;
    (void)argv;
	ft_bzero(&ms, sizeof(t_minish));
    init_ms(&ms, envp);
    set_signals(); //WIP - Preciso estudo
    read_inputs(&ms); //WIP
    ft_free_matrix(ms.env_list);
    return (g_exit_status); // finalizar o programa na main.
}

