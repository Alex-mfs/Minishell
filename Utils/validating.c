/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/10/28 19:03:15 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool validation_error(char *msg)
{
	printf("\033[1m""\033[31m""""Minishell:""\033[0m""%s\n", msg);
	//set_exit_status();
	return (false);
}

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
	//WIP Em vez disto, fazer verificação de quotes fechadas
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
	t_token	*curr;

	curr = ms->tk_list;
	if (curr->type == PIPE)
		return (false); //WIP Mensagem: "Input Syntax with Pipe"
	while (curr)
	{
		if (is_redirection(curr->token)
			&& (!curr->next || is_redir_or_pipe(curr->next->token)))
			return (false); //WIP Mensagem: "Input Syntax with Redirection"
		if (curr->type == PIPE
			&& (!curr->next || curr->next->type == PIPE))
			return (false); //WIP Mensagem: "Input Syntax with Pipe" //WIP talvez uma mensagem especifica a minishell
		curr = curr->next;
	}
	return (true);
}