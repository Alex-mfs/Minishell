/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ast_01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 00:04:00 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/12 21:49:39 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// CREATE EXECUTION NODE
t_cmd	*exec_node(void)
{
	t_exec	*node;

	node = (t_exec *)malloc(sizeof(*node));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(*node));
	node->type = EXEC;
	return ((t_cmd *)node);
}

// CREATE REDIRECTION NODE
t_cmd	*redir_node(t_cmd *sub_node, t_file *file)
{
	t_redir	*node;

	node = (t_redir *)malloc(sizeof(*node));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(*node));
	node->type = REDI;
	node->cmd = sub_node;
	node->file = file->file;
	node->mode = file->mode;
	node->fd = file->fd;
	return ((t_cmd *)node);
}

// CREATE PIPE NODE
t_cmd	*pipe_node(t_cmd *left, t_cmd *right)
{
	t_pipe	*node;

	node = (t_pipe *)malloc(sizeof(*node));
	if (!node)
	{
		left = free_tree(left);
		right = free_tree(right);
		return (NULL);
	}
	ft_memset(node, 0, sizeof(*node));
	node->type = PIPE;
	node->left = left;
	node->right = right;
	return ((t_cmd *)node);
}
