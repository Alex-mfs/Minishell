/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/29 01:20:32 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	merge_tokens(t_minish *ms)
{
	t_token	*curr;
	t_token	*next;

	curr = ms->tk_list;
	while (curr)
	{
		next = curr->next;
		if (!next)
			break ;
		if (!curr->to_merge && next->to_merge)
		{
			curr->token = ft_strbuild(curr->token, next->token);
			curr->next = next->next;
			curr->type = OTHER;
			free(next->token);
			free(next);
		}
		else
			curr = curr->next;
	}
}

static char	*find_name(char *token)
{
	int	pos;
	int	end;

	pos = ft_strchr_pos(token, '$');
	end = pos + 1;
	if (token[end] == '?')
		return (ft_strdup("$?"));
	else if (ft_isdigit(token[end]))
		return (ft_substr(token, pos, end + 1 - pos));
	while (token[end] && (ft_isalnum(token[end]) || token[end] == '_'))
		end++;
	return (ft_substr(token, pos, end - pos));
}

static void	expand_token(t_minish *ms, t_token *tk)
{
	char	*name;
	char	*value;
	char	*buff;

	while (ft_strchr(tk->token, '$'))
	{
		name = find_name(tk->token);
		if (ft_str_cmp(name, "$?"))
			value = ft_itoa(get_exit_status());
		else
			value = get_env(name, ms->env_tmp);
		buff = ft_str_repl_seg(tk->token, name, value);
		free(tk->token);
		tk->token = ft_strdup(buff);
		free(name);
		free(value);
		free(buff);
	}
}

void	expand(t_minish *ms)
{
	t_token	*curr;
	bool	dont_expand;

	curr = ms->tk_list;
	dont_expand = false;
	while (curr)
	{
		if (dont_expand)
			dont_expand = false;
		else
		{
			if (curr->type == DOUBLE_QUOTES || curr->type == OTHER)
				expand_token(ms, curr);
			if (!curr->token[0]
				&& (curr->type == DOUBLE_QUOTES || curr->type == SINGLE_QUOTES))
				curr->empty_quotes = true;
		}
		if (curr->type == REDIR_INPUT_2)
			dont_expand = true;
		curr = curr->next;
	}
	merge_tokens(ms);
}
