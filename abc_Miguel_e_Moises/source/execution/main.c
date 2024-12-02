/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 00:04:00 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/30 16:53:47 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_sig_num = 0;

int	main(int argc, char **argv, char **envp)
{
	t_data	*ms_data;
	char	**my_envs;
	int		return_code;

	(void)argv;
	if (argc != 1)
		return (EXIT_FAILURE);
	ms_data = NULL;
	handle_signals(ms_data);
	return_code = 0;
	my_envs = copy_environment(envp);
	if (!my_envs)
		return (EXIT_FAILURE);
	while (1)
	{
		if (g_sig_num == S_SIGINT)
			g_sig_num = NO_SIG;
		handle_signals(ms_data);
		init_shell(&ms_data, &my_envs, return_code);
		handle_input(ms_data, &my_envs, &return_code);
	}
	rl_clear_history();
	exit_minishell(ms_data, my_envs);
	return (0);
}

void	init_shell(t_data **ms_data, char ***my_envs, int return_code)
{
	*ms_data = init_minishell(*my_envs, return_code);
	delete_variables(*my_envs);
	*my_envs = NULL;
}

void	exit_minishell(t_data *ms_data, char **my_envs)
{
	(void)my_envs;
	write(1, "\033[1;31mExiting...\n\033[0m", 23);
	rl_clear_history();
	if (ms_data)
		clean_shell(ms_data);
	exit(EXIT_SUCCESS);
}
