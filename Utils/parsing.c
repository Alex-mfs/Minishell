/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/09/25 20:13:20 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*t_ast	*ast_new(t_token *token)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->token = token;
	node->args = ft_calloc(1, sizeof(char *));
	return (node);
}

void	ast_insert(t_ast **ast, t_ast *node, bool left)
{
	if (*ast && left)
		(*ast)->left = node;
	else if (*ast && !left)
		(*ast)->right = node;
	else
		*ast = node;
}

void	ast_destroy_node(t_ast *ast)
{
	token_destroy(ast->token);
	matrix_destroy(ast->args);
}

void	ast_clear(t_ast *ast, void (*del)(t_ast *))
{
	if (!ast)
		return ;
	ast_clear(ast->left, del);
	ast_clear(ast->right, del);
	del(ast);
	ft_free(ast);
}*/

/*t_token	*scanner(t_operation op)
{
	static t_list	*current = NULL;

	if (op == READ && current)
		return (current->content);
	else if (op == RESET)
		current = ms()->lexemes;
	else if (op == NEXT)
		current = current->next;
	else if (op == LOOKAHEAD && current->next)
		return (current->next->content);
	return (NULL);
}

void	parser(void)
{
	scanner(RESET);
	ms()->ast = _parse_pipeline();
}*/

static t_ast	*parse_pipe(t_ast *prev, t_ast *curr, t_minish *ms)
{
	/*	t_ast	*root;

	root = ast_new(token_new(ft_strdup("|"), LEX_PIPE, false));
	if (!root)
		return (NULL);
	ast_insert(&root, ast, true);
	ast_insert(&root, command, false);
		void	ast_insert(t_ast **ast, t_ast *node, bool left)
			if (*ast && left)
				(*ast)->left = node;
			else if (*ast && !left)
				(*ast)->right = node;
			else
				*ast = node;
	return (root);*/
	t_ast	*pip;

	pip = ft_calloc(1, sizeof(t_ast));
	if (!pip)
		return (NULL);
	pip->cmd = ft_calloc(2, sizeof(char *));
	if (!pip->cmd)
		return (NULL);
	pip->cmd = "|";
	if (lastpipe_index(ms->cmd_list) >= 0)
		pip->index = -1;
	else
		pip->index = lastpipe_index(ms->cmd_list) - 1;
	pip->left = prev;
	pip->right = curr;
	return (pip);
}

static t_token	*parse_redir(t_ast *cmd, t_token *tk)
{
	/*	t_ast	*redir;

	redir = ast_new(token_copy(scanner(READ)));
	if (!redir)
		return (NULL);
	scanner(NEXT);
	redir->args = matrix_append(redir->args, ft_strdup(scanner(READ)->str));
	redir->left = command->left;
	command->left = redir;
	return (command);*/
	t_ast	*redir;

	redir = ft_calloc(1, sizeof(t_ast));
	if (!redir)
		return (NULL);
	redir->cmd = tk->token;
	redir->args = ft_matrix_add_line(redir->args, ft_strdup(tk->next->token));
	if (tk->type == REDIR_INPUT_1 || tk->type == REDIR_INPUT_2) //WIP confirmar tudo!
		cmd->left = redir;
	else
		cmd->right = redir;
	return (tk->next);
}

static t_token	*parse_command(t_minish *ms, t_token *buff)
{
	/*
	t_ast	*cmd;

	cmd = ast_new(token_copy(scanner(READ)));
	if (!cmd)
		return (NULL);
	cmd->index = ms()->num_commands++;
	while (scanner(READ) && scanner(READ)->type != LEX_PIPE)
	{
		if (scanner(READ)->type >= LEX_IN_1 && scanner(READ)->type <= LEX_OUT_2)
			cmd = _extend_command(cmd);
		else
			cmd->args = matrix_append(cmd->args, ft_strdup(scanner(READ)->str));
		scanner(NEXT);
	}
	return (cmd);*/
	t_ast	*cmd;

	cmd = ft_calloc(1, sizeof(t_ast));
	if (!cmd)
		return (NULL);
	cmd->cmd = buff->token;
	cmd->next = NULL;
	ft_cmdlst_addback(&ms->cmd_list, cmd);
	buff = buff->next;
	while (buff && buff->type != PIPE)
	{
		if (buff->type >= REDIR_INPUT_1 && buff->type <= REDIR_OUTPUT_2)
			buff = parse_redir(cmd, buff); //WIP Redireções. Incompleto. Rever.
		else
			cmd->args = ft_matrix_add_line(cmd->args, ft_strdup(buff->token));
		buff = buff->next;
	}
	return (buff);
}

void	parse(t_minish *ms)
{
	/*	t_ast	*ast;
	t_ast	*command;

	command = NULL;
	ast = _parse_command();
	if (!ast)
		return (NULL);
	while (scanner(READ) && scanner(READ)->type == LEX_PIPE)
	{
		scanner(NEXT);
		command = _parse_command();
		ast = _extend_pipeline(ast, command);
	}
	return (ast);*/
	t_token	*buff;
	t_ast	*prev_cmd;
	t_ast	*curr_cmd;

	buff = parse_command(ms, ms->tk_list); //WIP parse_command original usa scanner, sem RESET. Confirmar que esta forma funciona
	if (!buff)
		return ;
	prev_cmd = ms->cmd_list;
	while (buff && buff->type == PIPE)
	{
		buff = parse_command(ms, buff->next); //Potenciais problemas de memória com buff. Ter atenção ao testar. WIP Redireções
		curr_cmd = ft_cmdlst_last(ms->cmd_list);
		prev_cmd = parse_pipe(prev_cmd, curr_cmd, ms);
	}
}