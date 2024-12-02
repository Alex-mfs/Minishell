/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ast_04.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:39:43 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/17 20:17:51 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// CHECK FOR EMPTY EXECUTION NODE WITH/WITHOUT REDIRECTION NODES
static int	check_empty_exec(t_exec *exec, t_cmd *node)
{
	t_redir	*node0;

	if (node)
	{
		if (!exec->argv)
		{
			if (node->type == EXEC)
				return (EXIT_FAILURE);
			else
			{
				node0 = (t_redir *)(node);
				while (node0->cmd->type != EXEC)
					node0 = (t_redir *)(node0->cmd);
				free_tree(node0->cmd);
				node0->cmd = NULL;
			}
		}
	}
	return (EXIT_SUCCESS);
}

// FILL DATA IN EXECUTION NODE + LOOK FOR REDIRECTIONS AFTER COMMAND
static int	fill_exec(t_data *ms_data, char **input, t_exec *exec, t_cmd **node)
{
	int		token;
	char	*stoken;
	char	*etoken;

	while (!look_token(input, "|"))
	{
		token = parse_token(ms_data, input, &stoken, &etoken);
		if (token == TOKEN_ERROR)
			return (EXIT_FAILURE);
		else if (token == TOKEN_EOF)
			return (check_empty_exec(exec, *node));
		stoken = substr_expans(ms_data, stoken, etoken);
		if (!stoken)
			return (EXIT_FAILURE);
		if (fill_argv(ms_data, stoken, exec) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		*node = parse_redir(ms_data, *node, input);
		if (!*node)
			return (EXIT_FAILURE);
	}
	if (look_token(input, "|") && !exec->argv)
		print_syntax_error(ms_data, TOKEN_PIPE);
	else
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

// PARSE EXECUTION
static t_cmd	*parse_exec(t_data *ms_data, char **input)
{
	t_cmd	*node;
	t_exec	*exec;

	node = check_node(ms_data, exec_node());
	if (!node)
		return (NULL);
	exec = (t_exec *)node;
	node = parse_redir(ms_data, node, input);
	if (!node)
		return (NULL);
	if (fill_exec(ms_data, input, exec, &node) == EXIT_FAILURE)
		node = free_tree(node);
	return (node);
}

// PARSE PIPE
t_cmd	*parse_pipe(t_data *ms_data, char **input)
{
	t_cmd	*pnode;
	t_cmd	*lnode;
	t_cmd	*rnode;

	lnode = parse_exec(ms_data, input);
	if (!lnode)
		return (NULL);
	if (look_token(input, "|"))
	{
		parse_token(ms_data, input, 0, 0);
		if (**input == '\0')
			print_syntax_error(ms_data, TOKEN_EOF);
		rnode = parse_pipe(ms_data, input);
		if (!rnode)
			return (free_tree(lnode));
		pnode = check_node(ms_data, pipe_node(lnode, rnode));
		if (!pnode)
			return (NULL);
		return (pnode);
	}
	return (lnode);
}
