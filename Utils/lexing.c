/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/07/30 16:25:20 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*t_token	*token_new(char *str, t_lexeme type, bool is_joinable)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = str;
	token->type = type;
	token->can_merge = is_joinable;
	return (token);
}

t_token	*token_copy(t_token *token)
{
	t_token	*dup;

	dup = token_new(ft_strdup(token->str), token->type, token->can_merge);
	if (!dup)
		return (NULL);
	return (dup);
}

void	token_destroy(t_token *token)
{
	if (!token)
		return ;
	ft_free(token->str);
	ft_free(token);
}

bool	_is_mergeable(char *str, char *match, int jump)
{
	if (!str[jump])
		return (false);
	if (!ft_strcmp(SYMBOLS, match) && ft_strchr(QUOTES, str[jump]))
		return (true);
	if (ft_strchr(QUOTES, match[0]) && !ft_strchr(SPECIAL, str[jump + 1]))
		return (true);
	return (false);
}

int	_lexer_push_token(char *str, t_lexeme lexeme, bool can_merge)
{
	t_token	*token;

	token = token_new(str, lexeme, can_merge);
	if (!token || !str)
		return (0);
	ft_lstadd_back(&ms()->lexemes, ft_lstnew(token));
	return (ft_strlen(str));
}

int	_lexer_find_match(char *match, char *input)
{
	int		jump;
	char	*token;
	bool	can_merge;

	jump = ft_strlen_sep(input, match);
	can_merge = _is_mergeable(input, match, jump);
	token = ft_substr(input, 0, jump);
	if (match[0] == '"')
		_lexer_push_token(token, LEX_DOUBLE_QUOTES, can_merge);
	else if (match[0] == '\'')
		_lexer_push_token(token, LEX_SINGLE_QUOTES, can_merge);
	else
		_lexer_push_token(token, LEX_TERM, can_merge);
	return (jump);
}*/

static int	save_token(t_minish *ms, char *cmd, t_lexer type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		ft_error_msg("Error while creating token");
	token->cmd = cmd;
	token->type = type;
	return ((int)ft_strlen(cmd));
}

void	lexer(t_minish *ms, char *input)
{
	/*int	i;

	i = 0;
	while (ms()->input[i])
	{
		if (ms()->input[i] == ' ')
			i++;
		else if (ms()->input[i] == '|')
			i += _lexer_push_token(ft_strdup("|"), LEX_PIPE, false);
		else if (!ft_strncmp(&ms()->input[i], "<<", 2))
			i += _lexer_push_token(ft_strdup("<<"), LEX_IN_2, false);
		else if (!ft_strncmp(&ms()->input[i], ">>", 2))
			i += _lexer_push_token(ft_strdup(">>"), LEX_OUT_2, false);
		else if (ms()->input[i] == '<')
			i += _lexer_push_token(ft_strdup("<"), LEX_IN_1, false);
		else if (ms()->input[i] == '>')
			i += _lexer_push_token(ft_strdup(">"), LEX_OUT_1, false);
		else if (ms()->input[i] == '"')
			i += _lexer_find_match("\"", &ms()->input[i + 1]) + 2;
		else if (ms()->input[i] == '\'')
			i += _lexer_find_match("'", &ms()->input[i + 1]) + 2;
		else
			i += _lexer_find_match(SYMBOLS, &ms()->input[i]);
	}*/
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			i++;
		else if (input[i] == '|')
			i += save_token(ms, input[i], PIPE);
		else if (input[i] == '<' && input[i + 1] == '<')
			i += save_token(ms, input[i], REDIR_INPUT_2);
		else if (input[i] == '>' && input[i + 1] == '>')
			i += save_token(ms, input[i], REDIR_OUTPUT_2);
		else if (input[i] == '<')
			i += save_token(ms, input[i], REDIR_INPUT_1);
		else if (input[i] == '>')
			i += save_token(ms, input[i], REDIR_OUTPUT_1);
		else if (input[i] == '"')
			//i += save_token;
		else if (input[i] == '\'')
			//i += save_token;
		else
			i += save_token(ms, input[i], REGULAR);
	}
}


