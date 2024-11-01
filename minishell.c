/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:52:25 by joao-rib          #+#    #+#             */
/*   Updated: 2024/10/28 19:22:06 by joao-rib         ###   ########.fr       */
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
	ft_free_matrix(ms.env_list); //WIP Isto faz-se no sanitize?
	ft_free_matrix(ms.env_tmp); //WIP Isto faz-se no sanitize?
	ft_free_matrix(ms.path); //WIP Isto faz-se no sanitize?
	return (g_exit_status);
}

//WIP Validating - Rever, testar, definir
//WIP Tokenizing - echo example"< Makefile"

//WIP validation_error - Qual o exit_status?
//WIP assign_var - Se houver variável para atribuir valor (ex.: BUFFER_SIZE=40), faz-se. Senão, apenas executar (espera, porque senão?)
//WIP sanitize_envp - Confirmar que env_list e env_tmp não estão trocadas

//WIP expanding - Testar quotes dentro de redirects, testar heredocs.
//WIP confirmar os efeitos de readline; gera memoryleaks, mas valgrind pode ignorar, investigar