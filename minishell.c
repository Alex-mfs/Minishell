/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:52:25 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/27 09:48:12 by joao-rib         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_minish	ms;

	(void)argc;
	(void)argv;
	ft_bzero(&ms, sizeof(t_minish));
	init_ms(&ms, envp);
	set_signals();
	read_inputs(&ms);
	ft_free_matrix(ms.env_list);
	ft_free_matrix(ms.env_tmp);
	ft_free_matrix(ms.path);
	return (g_exit_status);
}

//FIXED Expanding gera problemas de memoria
//FIXED Heredocs sem funcionar

//WIP > a.txt
//WIP memory leaks nas redirecoes

//WIP NORMINETTE
//WIP expanding+merge - Casos malucos //https://mellow-pruner-7c7.notion.site/minishell-0436106d8aba4f2aa7408a9b916adb07