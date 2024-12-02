/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:21:04 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/25 16:21:23 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_exec(t_cmd *node)
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
			printf(" %s", argv[i]);
			i++;
		}
	}
}

void	print_redir(t_cmd *node)
{
	t_redir	*redir_node;

	redir_node = (t_redir *)node;
	if (redir_node->fd == 0)
		printf(" < %s", redir_node->file);
	if (redir_node->fd == 1)
		printf(" > %s", redir_node->file);
	if (redir_node->cmd)
		print_tree(redir_node->cmd);
}

void	print_pipe(t_cmd *node)
{
	t_pipe	*pipe_node;

	pipe_node = (t_pipe *)node;
	print_tree(pipe_node->left);
	printf(" |");
	print_tree(pipe_node->right);
}

void	print_tree(t_cmd *node)
{
	if (node->type == PIPE)
		print_pipe(node);
	else if (node->type == REDI)
		print_redir(node);
	else if (node->type == EXEC)
		print_exec(node);
}
