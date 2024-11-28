/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_aux3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:56:02 by alfreire          #+#    #+#             */
/*   Updated: 2024/11/28 21:54:42 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_input_redirection(const char *type)
{
	return (ft_str_cmp(type, "<") || ft_str_cmp(type, "<<"));
}

bool	is_output_redirection(const char *type)
{
	return (ft_str_cmp(type, ">") || ft_str_cmp(type, ">>"));
}

bool	process_out_redirections(t_ast *node, t_minish *ms)
{
	t_ast	*redir_node;
	bool	redir_error;

	redir_error = false;
	redir_node = node->redirections;
	while (redir_node != NULL)
	{
		if (is_output_redirection(redir_node->cmd))
		{
			execute_redir(redir_node->cmd, redir_node->args[0], ms);
			if (ms->dont_execve)
			{
				redir_error = true;
				break ;
			}
		}
		redir_node = redir_node->next;
	}
	return (redir_error);
}

bool	process_redirections(t_ast *node, t_minish *ms)
{
	t_ast	*redir_node;
	bool	redir_error;

	redir_error = false;
	redir_node = node->redirections;
	while (redir_node != NULL)
	{
		if (is_input_redirection(redir_node->cmd))
		{
			execute_redir(redir_node->cmd, redir_node->args[0], ms);
			if (ms->dont_execve)
			{
				redir_error = true;
				break ;
			}
		}
		redir_node = redir_node->next;
	}
	if (redir_error)
		return (redir_error);
	else
		redir_error = process_out_redirections(node, ms);
	return (redir_error);
}
