/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:46:55 by alfreire          #+#    #+#             */
/*   Updated: 2024/11/28 21:59:28 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	need2be_parent(char *command, char *arg, t_minish *ms)
{
	bool	is_parent;

	is_parent = false;
	if (!command)
		return (is_parent);
	if (ms->qtd_pipes > 0)
	{
		ms->qtd_pipes--;
		return (false);
	}
	if (ft_str_cmp(command, "cd") == true)
		is_parent = true;
	else if (ft_str_cmp(command, "exit") == true)
		is_parent = true;
	else if (ft_str_cmp(command, "export") == true && arg != NULL)
		is_parent = true;
	else if (ft_str_cmp(command, "unset") == true)
		is_parent = true;
	return (is_parent);
}

bool	is_redirection(char *cmd)
{
	if (ft_strchr(cmd, '<') || ft_strchr(cmd, '>'))
		return (true);
	return (false);
}

bool	is_redir_or_pipe(char *cmd)
{
	if (ft_strchr(cmd, '|') || is_redirection(cmd))
		return (true);
	return (false);
}

void	error(char *str, int status)
{
	ft_putstr_fd(str, 2);
	set_exit_status(status);
}

void	error_execve(t_minish *ms)
{
	perror("execve");
	set_exit_status(1);
	sanitize_ms(ms, true);
}
