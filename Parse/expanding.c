/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/10/19 18:02:51 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*find_name(char *token)
{
	/*char	*tmp;
	int		len;

	len = 0;
	tmp = ft_strnstr(str, "$", ft_strlen(str));
	if (tmp[1] == '?')
		return (ft_strdup("$?"));
	while (ft_isalnum(tmp[len + 1]) || tmp[len + 1] == '_')
		len++;
	return (ft_substr(tmp, 0, len + 1));*/
	int	pos;
	int	end;

	pos = ft_strchr_pos(token, '$');
	end = pos;
	if (token[pos + 1] == '?')
		return (ft_strdup("$?"));
	while (token[pos] && !ft_isdelim(token[pos]))
		end++;
	return (ft_substr(token, pos, end - pos + 1));
}

static void	expand_token(t_minish *ms, t_token *tk)
{
	/*char	*value;
	char	*key;
	char	*tmp;

	while (ft_strnstr(token->str, "$", ft_strlen(token->str)))
	{
		key = _find_key(token->str);
		if (!ft_strcmp(key, "$?"))
			value = ft_itoa(ms()->exit_status);
		else
			value = get_env(key);
		tmp = token->str;
		token->str = ft_strreplace(token->str, key, value);
		ft_free(tmp);
		ft_free(value);
		ft_free(key);
	}*/
	char	*name;
	char	*value;
	char	*buff;

	while (ft_strchr(tk->token, '$'))
	{
		name = find_name(tk->token);
		if (ft_str_cmp(name, "$?"))
			value = ft_itoa(get_exit_status());
		else
			value = get_env(name, ms->env_list);
		buff = ft_strdup(tk->token);
		tk->token = ft_str_repl_seg(buff, name, value);
		free(name);
		free(value);
		free(buff);
	}
}

void	expand(t_minish *ms)
{
	/*t_list	*curr;
	t_token	*token;

	curr = ms()->lexemes;
	while (curr)
	{
		token = ((t_token *)curr->content);
		if (token->type == LEX_IN_2)
			curr = curr->next;
		else if (token->type == LEX_DOUBLE_QUOTES || token->type == LEX_TERM)
			_expand_variable(token);
		curr = curr->next;
	}
	merge_lexemes(ms()->lexemes);*/
	t_token	*curr;

	curr = ms->tk_list;
	while (curr)
	{
		if (curr->type == DOUBLE_QUOTES || curr->type == OTHER)
			expand_token(ms, curr);
		curr = curr->next;
	}
	//merge(ms); WIP what is merge? quotes are mergeable.
}

/*void	merge_lexemes(t_list *lexemes)
{
	t_list	*aux;
	t_token	*next_token;
	t_token	*curr_token;
	char	*tmp;

	while (lexemes)
	{
		curr_token = lexemes->content;
		if (!lexemes->next)
			return ;
		if (!curr_token->can_merge)
		{
			lexemes = lexemes->next;
			continue ;
		}
		next_token = lexemes->next->content;
		tmp = curr_token->str;
		curr_token->str = ft_strjoin(curr_token->str, next_token->str);
		free(tmp);
		curr_token->can_merge &= next_token->can_merge;
		aux = lexemes->next;
		lexemes->next = lexemes->next->next;
		ft_lstdelone(aux, (void *)token_destroy);
	}
}*/