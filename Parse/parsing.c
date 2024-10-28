/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/10/28 18:40:31 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_ast	*parse_pipe(t_ast *prev, t_ast *curr, t_minish *ms)
{
	t_ast	*pip;

    if (lastpipe_index(ms->cmd_list) >= 0)
        pip->index = -1;
    else
        pip->index = lastpipe_index(ms->cmd_list) - 1;

    pip->left = prev;
    pip->right = curr;

    // Adicionar depuração para verificar se a AST foi construída corretamente
    printf("Pipe criado com comando anterior: '%s' e próximo comando: '%s'\n", prev->cmd, curr->cmd);

    return pip;
}*/


// static t_token	*parse_redir(t_ast *cmd, t_token *tk)
// {
// 	/*	t_ast	*redir;

// 	redir = ast_new(token_copy(scanner(READ)));
// 	if (!redir)
// 		return (NULL);
// 	scanner(NEXT);
// 	redir->args = matrix_append(redir->args, ft_strdup(scanner(READ)->str));
// 	redir->left = command->left;
// 	command->left = redir;
// 	return (command);*/
// 	t_ast	*redir;

// 	redir = ft_calloc(1, sizeof(t_ast));
// 	if (!redir)
// 		return (NULL);
// 	redir->cmd = tk->token;
// 	redir->args = ft_matrix_add_line(redir->args, ft_strdup(tk->next->token));
// 	redir->left = NULL;
// 	redir->right = NULL;
// 	redir->next = NULL;
// 	if (tk->type == REDIR_INPUT_1 || tk->type == REDIR_INPUT_2)
// 		cmd->left = redir;
// 	else
// 		cmd->right = redir;
// 	printf("parse_redir: Redirecionamento '%s' para arquivo '%s'\n", redir->cmd, redir->args[0]);
// 	return (tk->next);
// }
///////////////////////////////////////
/////////////// estava usando a debaixo//////////////////////////////////////
///////////////
// static t_token *parse_redir(t_ast *cmd, t_token *tk, int *error)
// {
//     t_ast *redir;

//     // Inicializa o sinalizador de erro como 0 (sem erro)
//     *error = 0;

//     // Verifica se há um token de arquivo após o redirecionamento
//     if (!tk->next)
//     {
//         printf("Erro: redirecionamento '%s' sem arquivo associado\n", tk->token);
//         *error = 1;
//         return NULL;
//     }

//     redir = ft_calloc(1, sizeof(t_ast));
//     if (!redir)
//     {
//         perror("Erro ao alocar memória para redir");
//         *error = 1;
//         return NULL;
//     }

//     redir->cmd = ft_strdup(tk->token); // "<" ou ">"
//     redir->args = ft_matrix_add_line(redir->args, ft_strdup(tk->next->token)); // Nome do arquivo
//     redir->left = NULL;
//     redir->right = NULL;
//     redir->next = NULL;

//     // Define o redirecionamento no comando
//     if (tk->type == REDIR_INPUT_1 || tk->type == REDIR_INPUT_2)
//         cmd->left = redir;
//     else
//         cmd->right = redir;

//     printf("parse_redir: Redirecionamento '%s' para arquivo '%s'\n", redir->cmd, redir->args[0]);

//     // Avança dois tokens após o redirecionamento (operador + arquivo)
//     t_token *next_token = tk->next->next;
//     printf("parse_redir: avançando para próximo token após redirecionamento '%s', próximo token = %p, tipo = %d\n",
//            tk->token, next_token, next_token ? next_token->type : -1);

//     return next_token;
// }

static t_token *parse_redir(t_ast *cmd, t_token *tk, int *error)
{
    t_redir *redir;

    *error = 0;

    if (!tk->next)
    {
        printf("Erro: redirecionamento '%s' sem arquivo associado\n", tk->token);
        *error = 1;
        return NULL;
    }

    redir = ft_calloc(1, sizeof(t_redir));
    if (!redir)
    {
        perror("Erro ao alocar memória para redir");
        *error = 1;
        return NULL;
    }

    redir->type = ft_strdup(tk->token);
    redir->filename = ft_strdup(tk->next->token);
    redir->next = NULL;

    // Adicionar o redirecionamento à lista cmd->redirs
    if (cmd->redirs == NULL)
    {
        cmd->redirs = redir;
    }
    else
    {
        t_redir *curr = cmd->redirs;
        while (curr->next != NULL)
            curr = curr->next;
        curr->next = redir;
    }

    printf("parse_redir: Redirecionamento '%s' para arquivo '%s'\n", redir->type, redir->filename);

    // Avançar dois tokens (redirecionamento + arquivo)
    return tk->next->next;
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

// static t_token	*parse_command(t_minish *ms, t_token *buff, int *error)
// {
//     t_ast *cmd;

//     *error = 0; // Inicializa o sinalizador de erro como 0 (sem erro)

//     if (!buff)
//     {
//         return NULL;
//     }

//     cmd = ft_calloc(1, sizeof(t_ast));
//     if (!cmd)
//     {
//         printf("Erro: falha ao alocar memória para cmd\n");
//         *error = 1;
//         return NULL;
//     }

//     cmd->args = ft_calloc(1, sizeof(char *));
//     cmd->next = NULL;

//     // Itera sobre os tokens até encontrar um PIPE ou acabar a lista
//     while (buff && buff->type != PIPE)
//     {
//         printf("Processando token: '%s', tipo: %d\n", buff->token, buff->type);

//         // Se for redirecionamento, delegue para a função que trata redirecionamento
//         if (buff->type >= REDIR_INPUT_1 && buff->type <= REDIR_OUTPUT_2)
//         {
//             buff = parse_redir(cmd, buff, error);
//             printf("parse_command: Após parse_redir, buff = %p, tipo = %d\n", buff, buff ? buff->type : -1);
//             if (*error)
//             {
//                 printf("Erro: parse_redir retornou NULL devido a um erro\n");
//                 return NULL;
//             }
//             continue; // Reinicia o loop com o novo token
//         }
//         // Se o token for do tipo OTHER, ele é um comando ou argumento
//         else if (buff->type == OTHER)
//         {
//             if (!cmd->cmd) // Se ainda não temos um comando definido
//             {
//                 if (!buff->token)
//                 {
//                     printf("Erro: token de comando é NULL\n");
//                     *error = 1;
//                     return NULL;
//                 }
//                 cmd->cmd = ft_strdup(buff->token); // Define o comando
//                 printf("Comando definido: '%s'\n", cmd->cmd);
//                 cmdlst_addback(&ms->cmd_list, cmd); // Adiciona à lista de comandos
//             }
//             else // Caso contrário, trata como argumento adicional
//             {
//                 if (!buff->token)
//                 {
//                     printf("Erro: argumento é NULL\n");
//                     *error = 1;
//                     return NULL;
//                 }
//                 cmd->args = ft_matrix_add_line(cmd->args, ft_strdup(buff->token));
//                 printf("Argumento adicionado: '%s'\n", buff->token);
//             }
//         }
//         else
//         {
//             printf("Token inesperado encontrado: '%s', tipo: %d\n", buff->token, buff->type);
//             *error = 1;
//             return NULL;
//         }

//         // Avança para o próximo token
//         buff = buff->next;
//     }

//     // Verifica se o próximo token é NULL (fim da lista) ou PIPE
//     if (!buff)
//     {
//         printf("Fim da lista de tokens após o comando '%s'\n", cmd->cmd);
//         // Não define *error, pois é o fim esperado
//         return NULL; // Indica o fim do parsing sem erro
//     }

//     return buff; // Retorna o próximo token, que pode ser um PIPE ou NULL
// }
/////////////
////////////// como estava anteriormente esta acima!!!!! //////
//////////////

static t_ast *parse_command(t_minish *ms, t_token *buff, int *error)
{
	t_ast	*redir;

	redir = ft_calloc(1, sizeof(t_ast));
	if (!redir)
		return (NULL);
	redir->cmd = ft_strdup(tk->token);
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

// void	parse(t_minish *ms)
// {
// 	t_token *buff;
// 	t_ast *prev_cmd;
// 	t_ast *curr_cmd;
// 	int error = 0;

// 	printf("Iniciando parsing...\n");
// 	buff = parse_command(ms, ms->tk_list, &error); // Processa o primeiro comando
// 	if (error)
// 	{
// 		printf("Erro: parse_command retornou NULL devido a um erro\n");
// 		return ;
// 	}
// 	prev_cmd = ms->cmd_list;

// 	// Processa pipes e comandos subsequentes
// 	while (buff && buff->type == PIPE)
// 	{
// 		printf("Encontrado pipe, processando próximo comando...\n");
// 		printf("buff->next antes de parse_command: %p\n", buff->next);
// 		if (buff->next)
// 			printf("Tipo de buff->next: %d\n", buff->next->type);

// 		buff = parse_command(ms, buff->next, &error); // Processa o próximo comando
// 		if (error)
// 		{
// 			printf("Erro: parse_command retornou NULL devido a um erro2\n");
// 			return ;
// 		}
// 		if (!buff)
// 		{
// 			printf("Fim da lista de tokens após o comando '%s'\n", prev_cmd->cmd);
// 			break; // Saímos do loop pois terminamos de processar todos os comandos
// 		}

// 		curr_cmd = cmdlst_last(ms->cmd_list);
// 		prev_cmd = parse_pipe(prev_cmd, curr_cmd, ms);
// 		if (!prev_cmd)
// 		{
// 			printf("Erro ao criar AST para pipe\n");
// 			return;
// 		}
// 		printf("AST para pipe criada com sucesso\n");
// 	}

// 	printf("Parsing concluído\n");
// }

void parse(t_minish *ms)
{
	t_ast	*cmd;

	cmd = ft_calloc(1, sizeof(t_ast));
	if (!cmd)
		return (NULL);
	cmd->next = NULL;
	cmd->left = NULL;
	cmd->right = NULL;
	while (buff && buff->type != PIPE)
	{
		if (buff->type >= REDIR_INPUT_1 && buff->type <= REDIR_OUTPUT_2)
			buff = parse_redir(cmd, buff);
		else if (!cmd->cmd)
		{
			cmd->cmd = ft_strdup(buff->token);
			cmdlst_addback(&ms->cmd_list, cmd);
		}
		else
			cmd->args = ft_matrix_add_line(cmd->args, ft_strdup(buff->token));
		buff = buff->next;
	}
	if (!cmd->args)
		cmd->args = ft_matrix_add_line(cmd->args, ft_strdup("\0"));
	return (buff);
}

void	parse(t_minish *ms)
{
	t_token	*buff;
	t_ast	*prev_cmd;
	t_ast	*curr_cmd;

	buff = parse_command(ms, ms->tk_list);
	if (!buff)
		return ;
	prev_cmd = ms->cmd_list;
	while (buff && buff->type == PIPE)
	{
		buff = parse_command(ms, buff->next); //Potenciais problemas de memória com buff. Ter atenção ao testar.
		curr_cmd = cmdlst_last(ms->cmd_list);
		prev_cmd = parse_pipe(prev_cmd, curr_cmd, ms);
	}
}
