/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/30 12:05:30 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	next_pos(const char *str, size_t i, char c)
{
	size_t	len;

	if (!str)
		return (-1);
	len = ft_strlen(str);
	while (i <= len || (unsigned char)c == '\0')
	{
		if (str[i] == c)
			return ((int)i);
		i++;
	}
	return (-1);
}

static char	*ft_strchr_nodelim(const char *str, int c)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (!str)
		return (0);
	len = ft_strlen(str);
	while (i <= len || (unsigned char)c == '\0')
	{
		if (str[i] == (unsigned char)c && str[i + 1]
			&& (ft_isalnum(str[i + 1]) || ft_strchr("_?", str[i + 1])))
			return (&((char *)str)[i]);
		i++;
	}
	return (0);
}

static char	*find_name(char *token)
{
	int	pos;
	int	end;

	pos = ft_strchr_pos(token, '$');
	while (token[pos + 1]
		&& !(ft_isalnum(token[pos + 1]) || ft_strchr("_?", token[pos + 1])))
		pos = next_pos(token, (size_t)(pos + 1), '$');
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

	while (ft_strchr_nodelim(tk->token, '$'))
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
	if (ft_str_cmp(tk->token, "$") && tk->next && is_tk_quote(tk->next))
		ft_bzero(tk->token, 1);
}

void	expand(t_minish *ms)
{
	t_token	*curr;
	bool	dont_expand;

	curr = ms->tk_list;
	dont_expand = false;
	while (curr)
	{
		if (dont_expand && is_tk_merge(curr))
			;
		else if (dont_expand)
			dont_expand = false;
		else
		{
			if (curr->type == DOUBLE_QUOTES || curr->type == OTHER)
				expand_token(ms, curr);
			if (!curr->token[0] && is_tk_quote(curr))
				curr->empty_quotes = true;
		}
		if (curr->type == REDIR_INPUT_2)
			dont_expand = true;
		curr = curr->next;
	}
	merge_tokens(ms);
}
