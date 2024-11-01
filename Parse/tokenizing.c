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

static t_lexer	find_quotes(char *str)
{
	t_lexer	result;
	int		i;
	int		squote;
	int		dquote;

	i = 0;
	squote = 0;
	dquote = 0;
	while (str[i] && squote != 2 && dquote != 2)
	{
		if (str[i] == '\"' && dquote >= 0)
		{
			squote = -1;
			result = DOUBLE_QUOTES;
			dquote++;
		}
		else if (str[i] == '\'' && squote >= 0)
		{
			dquote = -1;
			result = SINGLE_QUOTES;
			squote++;
		}
		i++;
	}
	if (dquote != 2 && squote != 2)
		result = OTHER;
	free(str);
	return (result);
}

static bool	is_tk_delim(int c)
{
	if (c == ' ' || c == '<' || c == '>'
		|| c == '|' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (true);
	else
		return (false);
}

static int	save_token(t_minish *ms, char *symbol, t_lexer type, bool merge)
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
	token->to_merge = merge;
	if (!merge)
		ms->aux_merge = false;
	tklst_addback(&ms->tk_list, token);
	return ((int)ft_strlen(symbol));
}

static int	save_cmd(t_minish *ms, char *input, char limit)
{
	int		i;
	char	*content;
	t_lexer	merge_case;

	i = 0;
	if (limit == ' ')
	{
		while (input[i] && !is_tk_delim(input[i])) //!ft_strchr("<>| \t\n\v\f\r", input[i])
			i++;
		merge_case = find_quotes(ft_substr(input, 0, i)); //Elaborar ft_strchr_n(char*, char, int n)?
		if (merge_case == SINGLE_QUOTES)
			i = ft_strchr_pos(input, '\'');
		else if (merge_case == DOUBLE_QUOTES)
			i = ft_strchr_pos(input, '\"');
		//WIP echo example"< Makefile"
	}
	else
	{
		while (input[i] && input[i] != limit)
			i++;
		if (input[i] == '\0')
			return (-1);
	}
	content = ft_substr(input, 0, i); //WIP Aqui se aloca memoria. Incluir e pensar em salvaguardas
	if (limit == '\"')
		save_token(ms, content, DOUBLE_QUOTES, ms->aux_merge);
	else if (limit == '\'')
		save_token(ms, content, SINGLE_QUOTES, ms->aux_merge);
	else
		save_token(ms, content, OTHER, ms->aux_merge);
	free(content);
	ms->aux_merge = true;
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
			i += save_token(ms, "|", PIPE, false);
		else if (input[i] == '<' && input[i + 1] == '<')
			i += save_token(ms, "<<", REDIR_INPUT_2, false);
		else if (input[i] == '>' && input[i + 1] == '>')
			i += save_token(ms, ">>", REDIR_OUTPUT_2, false);
		else if (input[i] == '<')
			i += save_token(ms, "<", REDIR_INPUT_1, false);
		else if (input[i] == '>')
			i += save_token(ms, ">", REDIR_OUTPUT_1, false);
		else if (input[i] == '\"')
			i += 2 + save_cmd(ms, &input[i + 1], '\"');
		else if (input[i] == '\'')
			i += 2 + save_cmd(ms, &input[i + 1], '\'');
		else
			i += save_cmd(ms, &input[i], ' ');
		if (ft_isdelim(input[i - 1]))
			ms->aux_merge = false;
	}
}
