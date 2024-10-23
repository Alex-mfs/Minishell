/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/10/23 15:46:15 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	validate_quotes(char *input)
{
	/*int		i;
	char	quote;
	bool	in_quotes;

	i = -1;
	quote = '\"';
	in_quotes = false;
	if (is_spaces(ms()->input))
		return (false);
	while (ms()->input[++i])
	{
		if (in_quotes && ms()->input[i] == quote)
			in_quotes = false;
		else if (!in_quotes && ft_strchr("\"\'", ms()->input[i]))
		{
			quote = ms()->input[i];
			in_quotes = true;
		}
	}
	if (in_quotes)
		return (error(ANSI_RED, ERROR_UNCLOSED_QUOTES, NULL, 2));
	return (true);*/
	int	i;
	int	sq_count;
	int	dq_count;

	i = 0;
	sq_count = 0;
	dq_count = 0;
	while (input[i])
	{
		if (input[i] == '\"')
			dq_count++;
		else if (input[i] == '\'')
			sq_count++;
		i++;
	}
	if (dq_count % 2 || sq_count % 2)
		return (false);
	else
		return (true);
}

bool	validate_tokens(t_minish *ms)
{
	/*t_token	*next;
	int		num_pipes;
	int		num_commands;

	num_pipes = 0;
	num_commands = 1;
	scanner(RESET);
	if (is_redir_or_pipe(scanner(READ)))
		return (error(ANSI_RED, ERROR_SYNTAX, scanner(READ)->str, 2));
	while (scanner(READ))
	{
		next = scanner(LOOKAHEAD);
		if (is_redirection(scanner(READ)) && (!next || is_redir_or_pipe(next)))
			return (error(ANSI_RED, ERROR_UNCLOSED_RED, NULL, 2));
		if (scanner(READ)->type == LEX_PIPE)
		{
			num_pipes++;
			if (next && !is_redir_or_pipe(next))
				num_commands++;
		}
		scanner(NEXT);
	}
	if (num_pipes >= num_commands)
		return (error(ANSI_RED, ERROR_UNCLOSED_PIPES, NULL, 2));
	return (true);*/
	t_token	*curr;
	int		n_symbols;
	int		n_commands;

	n_symbols = 0;
	n_commands = 1;
	curr = ms->tk_list;
	while (curr)
	{
		if (curr->token == NULL || curr->token[0] == '\0')
		{
			printf("Erro: token vazio\n");
			return false;
		}
		printf("Validando token: %s, Tipo: %d\n", curr->token, curr->type);
		if (curr->type >= REDIR_INPUT_1 && curr->type <= PIPE)
		{
			n_symbols++;
			if (curr->next && curr->next->type > PIPE)
				n_commands++;
		}
		curr = curr->next;
	}
	if (n_symbols >= n_commands)
	{
		printf("Erro: número de símbolos é maior ou igual ao número de comandos.\n");
		return (false);
	}
	return (true);
}

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
}*/