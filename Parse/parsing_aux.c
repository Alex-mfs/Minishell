/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/30 15:11:41 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	empty_cmd(t_minish *ms, t_ast *node)
{
	if (!node->args)
		cmdlst_addback(&ms->cmd_list, node);
	else if (node->args && node->args[0][0])
	{
		if (node->cmd)
			free(node->cmd);
		node->cmd = ft_strdup(node->args[0]);
		node->args = ft_matrix_del_line_top(node->args);
	}
}
