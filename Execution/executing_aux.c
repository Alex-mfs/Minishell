/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:46:55 by alfreire          #+#    #+#             */
/*   Updated: 2024/12/06 15:22:23 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pick_function(t_ast *node, t_minish *ms, int tmp)
{
	if (ft_str_cmp(node->cmd, "pwd"))
		printf("%s\n", ms->cwd);
	else if (ft_str_cmp(node->cmd, "echo"))
		echo(node->args);
	else if (ft_str_cmp(node->cmd, "exit"))
		exit_bash(node->args, ms, tmp);
	else if (ft_str_cmp(node->cmd, "env"))
		env(node->args, ms->env_list);
	else if (ft_str_cmp(node->cmd, "export"))
		ft_export(node->args, ms);
	else if (ft_str_cmp(node->cmd, "unset"))
		unset(node->args, ms);
	else if (ft_str_cmp(node->cmd, "cd"))
		cd(node->args, ms);
}

bool	need2be_parent(char *command, char *arg, t_minish *ms)
{
	bool	is_parent;

	is_parent = false;
	if (!command)
		return (is_parent);
	if (lastpipe(ms->cmd_list)->index < 0)
		return (false);
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
