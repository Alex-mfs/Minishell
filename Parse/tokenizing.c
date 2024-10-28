/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/10/28 18:46:21 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	is_tk_delim(int c)
{
	if (c == ' ' || c == '<' || c == '>'
		|| c == '|' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (true);
	else
		return (false);
}

static int	save_token(t_minish *ms, char *symbol, t_lexer type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		ft_error_msg("Error while creating token");
	token->token = ft_strdup(symbol);
	if (!token->token)
		ft_error_msg("Error while saving token");
	token->type = type;
	token->next = NULL;
	tklst_addback(&ms->tk_list, token);
	return ((int)ft_strlen(symbol));
}

static int	save_cmd(t_minish *ms, char *input, char limit)
{
	int		i;
	char	*content;

	i = 0;
	if (limit == ' ')
	{
		while (input[i] && !is_tk_delim(input[i]))
			i++;
	}
	else
	{
		while (input[i] && input[i] != limit)
			i++;
	}
	if (input[i] == '\0' && (limit == '\'' || limit == '\"'))
		return (-1);
	content = ft_substr(input, 0, i); //WIP Aqui se aloca memoria. Incluir e pensar em salvaguardas
	if (limit == '\"')
		save_token(ms, content, DOUBLE_QUOTES);
	else if (limit == '\'')
		save_token(ms, content, SINGLE_QUOTES);
	else
		save_token(ms, content, OTHER);
	free(content);
	return (i);
}

void	get_tokens(t_minish *ms, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_isdelim(input[i]))
			i++;
		else if (input[i] == '|')
			i += save_token(ms, "|", PIPE);
		else if (input[i] == '<' && input[i + 1] == '<')
			i += save_token(ms, "<<", REDIR_INPUT_2);
		else if (input[i] == '>' && input[i + 1] == '>')
			i += save_token(ms, ">>", REDIR_OUTPUT_2);
		else if (input[i] == '<')
			i += save_token(ms, "<", REDIR_INPUT_1);
		else if (input[i] == '>')
			i += save_token(ms, ">", REDIR_OUTPUT_1);
		else if (input[i] == '\"')
			i += 2 + save_cmd(ms, &input[i + 1], '\"');
		else if (input[i] == '\'')
			i += 2 + save_cmd(ms, &input[i + 1], '\'');
		else
			i += save_cmd(ms, &input[i], ' ');
	}
	//WIP Entender o merge
}
//[bool]can_merge = _is_mergeable(input, match, jump);
/*bool	_is_mergeable(char *str, char *match, int jump)
{
	if (!str[jump])
		return (false);
	if (!ft_strcmp(SYMBOLS, match) && ft_strchr(QUOTES, str[jump]))
		return (true);
	if (ft_strchr(QUOTES, match[0]) && !ft_strchr(SPECIAL, str[jump + 1]))
		return (true);
	return (false);
}*/