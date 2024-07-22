/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:52:25 by joao-rib          #+#    #+#             */
/*   Updated: 2024/07/22 17:33:44 by joao-rib         ###   ########.fr       */
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
    init_ms(&ms, envp);
    //set_signals();
    //read_inputs();
    i = 0;
    while (ms.env_list[i])
    {
        ft_printf("No.%d: %s\n", i, ms.env_list[i]);
        i++;
    }
    return (0);
}

