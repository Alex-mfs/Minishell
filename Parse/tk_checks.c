/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/30 14:00:05 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_tk_redpip(t_token *tk)
{
	if (tk->type >= REDIR_INPUT_1 && tk->type <= PIPE)
		return (true);
	return (false);
}

bool	is_tk_quote(t_token	*tk)
{
	if (tk->type == DOUBLE_QUOTES || tk->type == SINGLE_QUOTES)
		return (true);
	else
		return (false);
}

bool	is_tk_merge(t_token	*tk)
{
	if (tk->to_merge)
		return (true);
	else if (tk->next && tk->next->to_merge)
		return (true);
	else
		return (false);
}
