/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialising.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/05 11:02:02 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_ms(t_minish *ms, char **envp)
{
	char	*path_env;

	ms->env_list = ft_matrix_dup(envp);
	ms->env_tmp = ft_matrix_dup(envp);
	ms->stdin_backup = dup(STDIN_FILENO); //WIP Talvez nao seja necessario..?
	ms->stdout_backup = dup(STDOUT_FILENO); //WIP Talvez nao seja necessario..?
	ms->cmd_list = NULL;
	ms->cwd = getcwd(NULL, 4096);
	ms->fd_in = 0;
	ms->fd_out = 1;
	path_env = getenv("PATH");
	if (path_env)
		ms->path = ft_split(path_env, ':');
	else
		ms->path = NULL;
	ms->aux_merge = false;
}
