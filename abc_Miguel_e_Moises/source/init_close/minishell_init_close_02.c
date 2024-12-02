/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init_close_02.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 22:28:28 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/27 02:41:46 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// FREE NODES IN NODES LST (ONE AT TIME)
static void	free_nodes_heredoc(t_cmd *node)
{
	t_pipe	*pipe_node;
	t_redir	*redir_node;

	if (node)
	{
		if (node->type == PIPE)
		{
			pipe_node = (t_pipe *)node;
			free(pipe_node->left);
			free(pipe_node->right);
			free(pipe_node);
		}
		else if (node->type == REDI)
		{
			redir_node = (t_redir *)node;
			free(redir_node->file);
			free(redir_node);
		}
		else if (node->type == EXEC)
			free_exec(node);
	}
}

// FUNCTION TO DELETE THE CONTENT OF LST NODE
void	ft_del(void *content)
{
	if (content)
	{
		free_nodes_heredoc((t_cmd *)content);
		content = NULL;
	}
}

// FREE LINKED LIST WITH NODES (LIST NODES ONLY - NOT CONTENT)
void	lst_clean(t_list **lst)
{
	t_list	*lst0;
	t_list	*lst1;

	if (*lst != NULL)
	{
		lst0 = *lst;
		lst1 = lst0->next;
		while (lst1 != NULL)
		{
			free(lst0);
			lst0 = lst1;
			lst1 = lst1->next;
		}
		free(lst0);
		*lst = NULL;
	}
}
