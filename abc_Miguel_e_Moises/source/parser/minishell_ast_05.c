/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ast_05.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 21:00:05 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/27 17:23:39 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// MAIN PARSING FUNCTION
t_cmd	*create_tree(t_data *ms_data)
{
	t_cmd	*tree;
	char	*input;

	input = ms_data->input;
	tree = parse_pipe(ms_data, &input);
	return (tree);
}
