/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/30 14:00:12 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	validation_error(char *msg)
{
	printf("\033[1m""\033[31m""""Error: ""\033[0m""%s\n", msg);
	set_exit_status(2);
	return (false);
}

static int	find_match(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == quote)
			return (i + 1);
		i++;
	}
	return (0);
}

bool	validate_quotes(char *input)
{
	int		i;
	int		check;

	i = 0;
	while (input[i])
	{
		check = i;
		if (input[i] == '\"' || input[i] == '\'')
		{
			i += find_match(input + i, input[i]);
			if (i == check)
				return (validation_error("Unclosed quotes"));
		}
		else
			i++;
	}
	return (true);
}

bool	validate_tokens(t_minish *ms)
{
	t_token	*curr;

	curr = ms->tk_list;
	if (curr->type == PIPE)
		return (validation_error("Input syntax near pipe"));
	while (curr)
	{
		if ((curr->type >= REDIR_INPUT_1 && curr->type <= REDIR_OUTPUT_2)
			&& (!curr->next || is_tk_redpip(curr->next)))
			return (validation_error("Input syntax near redirection"));
		if (curr->type == PIPE
			&& (!curr->next || curr->next->type == PIPE))
			return (validation_error("Unclosed pipe"));
		curr = curr->next;
	}
	return (true);
}
