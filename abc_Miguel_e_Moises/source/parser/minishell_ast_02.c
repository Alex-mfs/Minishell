/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ast_02.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 00:18:58 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/27 02:45:06 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// CREATE NEW REDIRECTION NODE IN SEQUENTIAL ORDER
t_cmd	*seq_redir(t_data *ms_data, t_cmd *node, t_file *file)
{
	t_redir	*node0;
	t_cmd	*node1;

	if (node->type == EXEC)
	{
		node1 = check_node(ms_data, redir_node(node, file));
		if (!node1)
			node = free_tree(node);
		else
			node = node1;
	}
	else
	{
		node0 = (t_redir *)(node);
		while (node0->cmd->type != EXEC)
			node0 = (t_redir *)(node0->cmd);
		node1 = check_node(ms_data, redir_node(node0->cmd, file));
		if (!node1)
			node = free_tree(node);
		else
			node0->cmd = node1;
	}
	return (node);
}

// CREATE FILE STRUCT WITH FILE DETAILS FOR REDIRECTION NODES
static t_file	*file_details(t_data *ms_data, int token, char *stoken)
{
	t_file	*file;

	file = check_file(ms_data, (t_file *)malloc(sizeof(*file)));
	if (!file)
		return (NULL);
	ft_memset(file, 0, sizeof(*file));
	file->file = stoken;
	if (token == TOKEN_INPU)
	{
		file->mode = O_RDONLY;
		file->fd = STDIN_FILENO;
	}
	else if (token == TOKEN_OUTP)
	{
		file->mode = O_WRONLY | O_TRUNC | O_CREAT;
		file->fd = STDOUT_FILENO;
	}
	else if (token == TOKEN_APPE)
	{
		file->mode = O_WRONLY | O_CREAT | O_APPEND;
		file->fd = STDOUT_FILENO;
	}
	return (file);
}

static t_cmd	*redir_type(t_data *ms_data, int token, t_cmd *node, \
char *stoken)
{
	t_file	*file;

	if (token == TOKEN_INPU || token == TOKEN_OUTP || token == TOKEN_APPE)
	{
		file = file_details(ms_data, token, stoken);
		if (!file)
			node = free_tree(node);
		else
			node = seq_redir(ms_data, node, file);
		free(file);
		if (!node)
			free(stoken);
	}
	else if (token == TOKEN_DELI)
		node = heredoc_node(ms_data, node, stoken);
	return (node);
}

// PARSE REDIRECTION
t_cmd	*parse_redir(t_data *ms_data, t_cmd *node, char **input)
{
	int		token;
	int		next_token;
	char	*stoken;
	char	*etoken;

	while (look_token(input, "<>"))
	{
		token = parse_token(ms_data, input, 0, 0);
		next_token = parse_token(ms_data, input, &stoken, &etoken);
		if (next_token == TOKEN_ERROR || next_token != TOKEN_TEXT)
		{
			if (next_token != TOKEN_TEXT)
				print_syntax_error(ms_data, next_token);
			return (free_tree(node));
		}
		stoken = check_red(ms_data, check_str(ms_data, substr(stoken, etoken)), \
		substr_expans(ms_data, stoken, etoken));
		if (!stoken)
			return (free_tree(node));
		node = redir_type(ms_data, token, node, stoken);
		if (!node)
			break ;
	}
	return (node);
}
