/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_check_error_01.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:36:14 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/27 02:44:05 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// PRINT ERROR IF NODE WAS NOT CREATED
t_cmd	*check_node(t_data *ms_data, t_cmd *node)
{
	t_list	*lst_node;

	if (!node)
		print_error(ms_data, MALLOC, "");
	else
	{
		lst_node = ft_lstnew(node);
		if (!lst_node)
		{
			print_error(ms_data, MALLOC, "");
			node = free_tree(node);
		}
		else
			ft_lstadd_back(&(ms_data->lst_nodes), lst_node);
	}
	return (node);
}

// PRINT ERROR IF STRING WAS NOT ALLOCATED
char	*check_str(t_data *ms_data, char *str)
{
	if (!str)
		print_error(ms_data, MALLOC, "");
	return (str);
}

// PRINT ERROR IF STRING 2D WAS NOT ALLOCATED
char	**check_str_2d(t_data *ms_data, char **str)
{
	if (!str)
		print_error(ms_data, MALLOC, "");
	return (str);
}

// PRINT ERROR IF FILE WAS NOT CREATED
int	check_fd(t_data *ms_data, int fd)
{
	if (fd == -1)
	{
		perror("minishell: error creating heredoc file");
		ms_data->return_code = GENERAL_ERROR;
	}
	return (fd);
}

// PRINT ERROR IF READLINE RETURNED NULL
char	*check_readline(t_data *ms_data, char *str, char *delimiter)
{
	if (!str)
		print_error(ms_data, HEREDOC_CTRL_D, delimiter);
	return (str);
}
