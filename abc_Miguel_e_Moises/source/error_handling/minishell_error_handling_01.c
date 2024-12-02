/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error_handling_01.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:46:10 by madao-da          #+#    #+#             */
/*   Updated: 2024/11/30 18:46:12 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_return_code(t_data *ms_data, int error_code)
{
	if (error_code == MALLOC || error_code == FORK || error_code == REDIR_FILE)
		ms_data->return_code = GENERAL_ERROR;
	if (error_code == SYNTAX || error_code == QUOTE)
		ms_data->return_code = SHELL_BUILT_IN;
	if (error_code == ARG_LIMIT || error_code == HEREDOC)
		ms_data->return_code = CMD_NOT_EXEC;
}

// PRINT ERROR MESSAGE WITH SPECIFIC INFORMATION FOR QUOTES
void	print_error_msg_quotes(char *msg, char *info)
{
	ft_putstr_fd(MSG_MINISHELL, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	write(STDERR_FILENO, info, 1);
	write(STDERR_FILENO, "\n", 1);
}
