/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/10/25 01:56:07 by alfreire         ###   ########.fr       */
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

// static t_ast	*parse_pipe(t_ast *prev, t_ast *curr, t_minish *ms)
// {
// 	/*	t_ast	*root;

// 	root = ast_new(token_new(ft_strdup("|"), LEX_PIPE, false));
// 	if (!root)
// 		return (NULL);
// 	ast_insert(&root, ast, true);
// 	ast_insert(&root, command, false);
// 		void	ast_insert(t_ast **ast, t_ast *node, bool left)
// 			if (*ast && left)
// 				(*ast)->left = node;
// 			else if (*ast && !left)
// 				(*ast)->right = node;
// 			else
// 				*ast = node;
// 	return (root);*/
// 	t_ast	*pip;

// 	pip = ft_calloc(1, sizeof(t_ast));
// 	if (!pip)
// 		return (NULL);
// 	pip->cmd = ft_calloc(2, sizeof(char *));
// 	if (!pip->cmd)
// 		return (NULL);
// 	pip->cmd = ft_strdup("|");
// 	if (lastpipe_index(ms->cmd_list) >= 0)
// 		pip->index = -1;
// 	else
// 		pip->index = lastpipe_index(ms->cmd_list) - 1;
// 	pip->left = prev;
// 	pip->right = curr;
// 	return (pip);
// }
static t_ast *parse_pipe(t_ast *prev, t_ast *curr, t_minish *ms)
{
    t_ast *pip;

    pip = ft_calloc(1, sizeof(t_ast));
    if (!pip) {
        printf("Erro: falha ao alocar memória para o pipe\n");
        return NULL;
    }
    pip->cmd = ft_strdup("|");
    if (!pip->cmd) {
        printf("Erro: falha ao definir comando pipe\n");
        return NULL;
    }

    if (lastpipe_index(ms->cmd_list) >= 0)
        pip->index = -1;
    else
        pip->index = lastpipe_index(ms->cmd_list) - 1;

    pip->left = prev;
    pip->right = curr;

    // Adicionar depuração para verificar se a AST foi construída corretamente
    printf("Pipe criado com comando anterior: '%s' e próximo comando: '%s'\n", prev->cmd, curr->cmd);

    return pip;
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
	redir->left = NULL;
	redir->right = NULL;
	redir->next = NULL;
	if (tk->type == REDIR_INPUT_1 || tk->type == REDIR_INPUT_2)
		cmd->left = redir;
	else
		cmd->right = redir;
	return (tk->next);
}

// static t_token	*parse_command(t_minish *ms, t_token *buff)
// {
// 	/*
// 	t_ast	*cmd;

// 	cmd = ast_new(token_copy(scanner(READ)));
// 	if (!cmd)
// 		return (NULL);
// 	cmd->index = ms()->num_commands++;
// 	while (scanner(READ) && scanner(READ)->type != LEX_PIPE)
// 	{
// 		if (scanner(READ)->type >= LEX_IN_1 && scanner(READ)->type <= LEX_OUT_2)
// 			cmd = _extend_command(cmd);
// 		else
// 			cmd->args = matrix_append(cmd->args, ft_strdup(scanner(READ)->str));
// 		scanner(NEXT);
// 	}
// 	return (cmd);*/
// 	t_ast	*cmd;

// 	cmd = ft_calloc(1, sizeof(t_ast));
// 	if (!cmd)
// 		return (NULL);
// 	cmd->next = NULL;
// 	cmd->left = NULL;
// 	cmd->right = NULL;
// 	cmd->args = ft_calloc(1, sizeof(char *));
// 	while (buff && buff->type != PIPE)
// 	{
// 		if (buff->type >= REDIR_INPUT_1 && buff->type <= REDIR_OUTPUT_2)
// 			buff = parse_redir(cmd, buff);
// 		else if (!cmd->cmd)
// 		{
// 			cmd->cmd = buff->token;
// 			cmdlst_addback(&ms->cmd_list, cmd);
// 		}
// 		else
// 			cmd->args = ft_matrix_add_line(cmd->args, ft_strdup(buff->token));
// 		buff = buff->next;
// 	}
// 	return (buff);
// }

static t_token *parse_command(t_minish *ms, t_token *buff)
{
    t_ast *cmd;

    if (!buff)
    {
        return NULL;
    }

    cmd = ft_calloc(1, sizeof(t_ast));
    if (!cmd)
    {
        printf("Erro: falha ao alocar memória para cmd\n");
        return NULL;
    }

    cmd->args = ft_calloc(1, sizeof(char *));
    cmd->next = NULL;

    // Itera sobre os tokens até encontrar um PIPE ou acabar a lista
    while (buff && buff->type != PIPE)
    {
        // Verificar o valor do token
        printf("Processando token: '%s', tipo: %d\n", buff->token, buff->type);

        // Se for redirecionamento, delegue para a função que trata redirecionamento
        if (buff->type >= REDIR_INPUT_1 && buff->type <= REDIR_OUTPUT_2)
        {
            buff = parse_redir(cmd, buff);
            if (!buff)
            {
                printf("Erro: parse_redir retornou NULL\n");
                return NULL;
            }
        }
        // Se o token for do tipo OTHER, ele é um comando ou argumento
        else if (buff->type == OTHER)
        {
            if (!cmd->cmd) // Se ainda não temos um comando definido
            {
                if (!buff->token)
                {
                    printf("Erro: token de comando é NULL\n");
                    return NULL;
                }
                cmd->cmd = ft_strdup(buff->token); // Define o comando
                printf("Comando definido: '%s'\n", cmd->cmd);
                cmdlst_addback(&ms->cmd_list, cmd); // Adiciona à lista de comandos
            }
            else // Caso contrário, trata como argumento adicional
            {
                if (!buff->token)
                {
                    printf("Erro: argumento é NULL\n");
                    return NULL;
                }
                cmd->args = ft_matrix_add_line(cmd->args, ft_strdup(buff->token));
                printf("Argumento adicionado: '%s'\n", buff->token);
            }
        }
        else
        {
            printf("Token inesperado encontrado: '%s', tipo: %d\n", buff->token, buff->type);
            return NULL;
        }

        // Avança para o próximo token
        buff = buff->next;
    }

    // Verifica se o próximo token é NULL (fim da lista) ou PIPE
    if (!buff)
    {
        printf("Fim da lista de tokens após o comando '%s'\n", cmd->cmd);
        return NULL; // Retorno correto para indicar o fim do parsing
    }

    return buff; // Retorna o próximo token, que pode ser um PIPE ou NULL
}

// void	parse(t_minish *ms)
// {
// 	/*	t_ast	*ast;
// 	t_ast	*command;

// 	command = NULL;
// 	ast = _parse_command();
// 	if (!ast)
// 		return (NULL);
// 	while (scanner(READ) && scanner(READ)->type == LEX_PIPE)
// 	{
// 		scanner(NEXT);
// 		command = _parse_command();
// 		ast = _extend_pipeline(ast, command);
// 	}
// 	return (ast);*/
// 	t_token	*buff;
// 	t_ast	*prev_cmd;
// 	t_ast	*curr_cmd;

// 	printf("Iniciando parsing...\n");
// 	buff = parse_command(ms, ms->tk_list); //WIP parse_command original usa scanner, sem RESET. Confirmar que esta forma funciona
//     if (!buff)
//     {
//         printf("Erro: parse_command retornou NULL\n");
//         return ;
//     }
// 	prev_cmd = ms->cmd_list;
// 	while (buff && buff->type == PIPE)
// 	{
// 		printf("Encontrado pipe, processando próximo comando...\n");
// 		printf("buff->next antes de parse_command: %p\n", buff->next);
// 		if (buff->next)
// 			printf("Tipo de buff->next: %d\n", buff->next->type);

// 		buff = parse_command(ms, buff->next); //Potenciais problemas de memória com buff. Ter atenção ao testar.
// 		if (!buff)
//         {
//             printf("Erro: parse_command retornou NULL após o pipe\n");
//             return; // Tratamento de erro, se necessário
//         }
// 		curr_cmd = cmdlst_last(ms->cmd_list);
// 		prev_cmd = parse_pipe(prev_cmd, curr_cmd, ms);
// 		if (!prev_cmd)
//         {
//             printf("Erro ao criar AST para pipe\n");
//             return;
//         }
// 		printf("AST para pipe criada com sucesso\n");
// 	}
// 	printf("Parsing concluído\n");
// }

void parse(t_minish *ms)
{
    t_token *buff;
    t_ast   *prev_cmd;
    t_ast   *curr_cmd;

    printf("Iniciando parsing...\n");
    buff = parse_command(ms, ms->tk_list); // Processa o primeiro comando
    if (!buff)
    {
        printf("Erro: parse_command retornou NULL\n");
        return;
    }
    prev_cmd = ms->cmd_list;
    
    // Processa pipes e comandos subsequentes
    while (buff && buff->type == PIPE)
    {
        printf("Encontrado pipe, processando próximo comando...\n");
        printf("buff->next antes de parse_command: %p\n", buff->next);
        if (buff->next)
            printf("Tipo de buff->next: %d\n", buff->next->type);

        buff = parse_command(ms, buff->next); // Processa o próximo comando
        if (!buff) 
        {
            printf("Fim da lista de tokens após o comando '%s'\n", prev_cmd->cmd);
            break; // Saímos do loop pois terminamos de processar todos os comandos
        }

        curr_cmd = cmdlst_last(ms->cmd_list);
        prev_cmd = parse_pipe(prev_cmd, curr_cmd, ms);
        if (!prev_cmd)
        {
            printf("Erro ao criar AST para pipe\n");
            return;
        }
        printf("AST para pipe criada com sucesso\n");
    }

    printf("Parsing concluído\n");
}
