/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/10/24 11:41:12 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*find_name(char *token)
{
	int	pos;
	int	end;

	pos = ft_strchr_pos(token, '$');
	end = pos;
	if (token[pos + 1] == '?')
		return (ft_strdup("$?"));
	while (token[end] && !ft_isdelim(token[end]))
		end++;
	return (ft_substr(token, pos, end - pos + 1));
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
		buff = ft_strdup(tk->token);
		tk->token = ft_str_repl_seg(buff, name, value);
		free(name);
		free(value);
		free(buff);
	}
}

void	expand(t_minish *ms)
{
	t_token	*curr;

	curr = ms->tk_list;
	while (curr)
	{
		if (curr->type == DOUBLE_QUOTES || curr->type == OTHER) //Pode dar erro em redirects. Testar.
			expand_token(ms, curr);
		curr = curr->next;
	}
	//merge(ms); WIP Entender o merge.
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