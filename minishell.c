/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:52:25 by joao-rib          #+#    #+#             */
/*   Updated: 2024/09/16 21:57:04 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_minish    ms;
    int         i;

    (void)argc;
    (void)argv;
	ft_bzero(&ms, sizeof(t_minish));
    init_ms(&ms, envp); //WIP inicializar EXIT_STATUS
    set_signals(); //WIP - Preciso estudo
    read_inputs(&ms); //WIP
    /*i = 0;
    while (ms.env_list[i])
    {
        ft_printf("No.%d: %s\n", i, ms.env_list[i]);
        i++;
    }*/
    ft_free_matrix(ms.env_list);
    return (0);
}

