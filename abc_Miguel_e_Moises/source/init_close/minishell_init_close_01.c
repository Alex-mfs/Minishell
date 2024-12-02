/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init_close_01.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 19:18:50 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/27 15:10:10 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// FREES STRING AND SETS POINTER TO NULL
char	*free_str(char *str)
{
	free(str);
	return (NULL);
}

// FREE EXECUTION NODE
void	free_exec(t_cmd *node)
{
	t_exec	*exec_node;
	char	**argv;
	int		i;

	exec_node = (t_exec *)node;
	if (exec_node->argv)
	{
		argv = exec_node->argv;
		i = 0;
		while (argv[i])
		{
			free(argv[i]);
			i++;
		}
		free(argv);
		exec_node->argv = NULL;
	}
	free(node);
}

// FREE REDIRECTION NODE
static void	free_redir(t_cmd *node)
{
	t_redir	*redir_node;

	redir_node = (t_redir *)node;
	free(redir_node->file);
	redir_node->cmd = free_tree(redir_node->cmd);
	free(node);
}

// FREE PIPE NODE
static void	free_pipe(t_cmd *node)
{
	t_pipe	*pipe_node;

	pipe_node = (t_pipe *)node;
	pipe_node->left = free_tree(pipe_node->left);
	pipe_node->right = free_tree(pipe_node->right);
	free(node);
}

// FREE ABSTRACT SYNTAX TREE
t_cmd	*free_tree(t_cmd *node)
{
	if (node)
	{
		if (node->type == PIPE)
			free_pipe(node);
		else if (node->type == REDI)
			free_redir(node);
		else if (node->type == EXEC)
			free_exec(node);
	}
	return (NULL);
}
