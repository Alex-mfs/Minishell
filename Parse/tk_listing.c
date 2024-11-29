/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_listing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/28 21:05:27 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	merge_tokens(t_minish *ms)
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

t_token	*clear_top_token(t_token *node)
{
	t_token	*tmp;

	tmp = node->next;
	free(node->token);
	free(node);
	return (tmp);
}

bool	token_assign(t_token *buff)
{
	while (buff && buff->token)
	{
		if (!ft_strchr(buff->token, '='))
			return (false);
		buff = buff->next;
	}
	return (true);
}

static t_token	*tklst_last(t_token *lst)
{
	t_token	*ult;

	if (!lst)
		return (NULL);
	ult = lst;
	while (ult->next != NULL)
		ult = ult->next;
	return (ult);
}

void	tklst_addback(t_token **lst, t_token *new)
{
	t_token	*ultima;

	if (lst && new)
	{
		if (*lst)
		{
			ultima = tklst_last(*lst);
			ultima->next = new;
		}
		else
			*lst = new;
	}
}
