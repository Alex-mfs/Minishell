/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/29 18:00:55 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *process_escape_sequences(char *input) {
    char *output = ft_calloc(ft_strlen(input) + 1, sizeof(char));
    int i = 0, j = 0;

    while (input[i]) {
        if (input[i] == '\\' && input[i + 1]) {
            i++;
            if (input[i] == 'n')
                output[j++] = '\n';
            else if (input[i] == 't')
                output[j++] = '\t';
            // Handle other escape sequences as needed
            else
                output[j++] = input[i];
        } else {
            output[j++] = input[i];
        }
        i++;
    }
    return output;
}

int save_ansi_c_string(t_minish *ms, char *input)
{
	int i = 0;
	char *content;
	char *processed_content;

	// Find the closing single quote
	while (input[i] && input[i] != '\'')
		i++;
	if (input[i] != '\'')
	{
		error("minishell: Unclosed ANSI-C quote\n", 1);
		return (i);
	}
	// Extract the content inside the quotes
	content = ft_substr(input, 0, i);
	// Process escape sequences if you want to support them
	processed_content = process_escape_sequences(content);
	free(content);
	// Save the processed content as a token
	save_token(ms, processed_content, OTHER, ms->aux_merge);
	free(processed_content);
	ms->aux_merge = true;
	return i + 1; // Return the number of characters consumed
}

static char	*ft_strchr_nodelim(const char *str, int c)
{
	size_t	i;
	size_t	len;

	if (!str)
		return (NULL);
	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == (unsigned char)c && str[i + 1])
		{
			if (ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?' || str[i + 1] == '$')
				return (&((char *)str)[i]);
		}
		i++;
	}
	return (NULL);
}

static char	*find_name(char *token)
{
	int	pos;
	int	end;

	pos = ft_strchr_pos(token, '$');
	if (pos == -1)
		return (NULL);
	if (token[pos + 1] == '\0')
		return (ft_strdup("$"));
	else if (token[pos + 1] == '?')
		return (ft_substr(token, pos, 2));
	else if (ft_isdigit(token[pos + 1]))
		return (ft_substr(token, pos, 2));
	else if (ft_isalpha(token[pos + 1]) || token[pos + 1] == '_')
	{
		end = pos + 2;
		while (token[end] && (ft_isalnum(token[end]) || token[end] == '_'))
			end++;
		return (ft_substr(token, pos, end - pos));
	}
	else
		return (ft_substr(token, pos, 1));
}

static void	expand_token(t_minish *ms, t_token *tk)
{
	char	*name;
	char	*value;
	char	*buff;

	while (ft_strchr_nodelim(tk->token, '$'))
	{
		name = find_name(tk->token);
		if (!name)
			break ;
		if (ft_str_cmp(name, "$?"))
			value = ft_itoa(get_exit_status());
		else if (ft_str_cmp(name, "$"))
			value = ft_strdup("$");
		else
			value = get_env(name + 1, ms->env_tmp);
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
