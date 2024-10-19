/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialising.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/10/17 17:57:48 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*void	_ms_init(char **envp)
{
	ft_bzero(ms(), sizeof(t_ms));
	(ms()->envlist) = envlist(envp);
	update_envs();
	(ms()->exit_status) = 0;
	(ms()->cwd) = getcwd(NULL, 4096);
	(ms()->in_fd) = STDIN_FILENO;
	(ms()->out_fd) = STDOUT_FILENO;
	return ;
}*/

static char	*trim_name(char *to_trim)
{
	char	*trimmed;

	trimmed = ft_strdup(ft_strchr(to_trim, '=') + 1);
	free(to_trim);
	return (trimmed);
}

void	init_ms(t_minish *ms, char **envp)
{
	int	i;

	i = 0;
	ms->env_list = ft_matrix_dup(envp);
	ms->env_tmp = ft_matrix_dup(envp);
	while (i < 50)
	{
		ms->env_list[i] = trim_name(ms->env_list[i]);
		i++;
	}
	ms->cwd = getcwd(NULL, 4096);
	ms->fd_in = 0;
	ms->fd_out = 1;
}
