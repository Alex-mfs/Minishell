/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error_handling_02.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:46:16 by madao-da          #+#    #+#             */
/*   Updated: 2024/11/30 18:46:18 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// PRINT ERROR MESSAGE WITH SPECIFIC INFORMATION FOR HEREDOC
static void	print_error_msg_hdoc(char *msg, char *info)
{
	ft_putstr_fd(MSG_MINISHELL, STDERR_FILENO);
	if (*info == '\0')
		ft_putendl_fd(msg, STDERR_FILENO);
	else
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(info, STDERR_FILENO);
		ft_putendl_fd("')", STDERR_FILENO);
	}
}

// PRINT ERROR MESSAGE WITH SPECIFIC INFORMATION
static void	print_error_msg(char *msg, char *info)
{
	ft_putstr_fd(MSG_MINISHELL, STDERR_FILENO);
	if (*info == '\0')
		ft_putendl_fd(msg, STDERR_FILENO);
	else
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putendl_fd(info, STDERR_FILENO);
	}
}

// PRINT ERROR MESSAGE WITH SPECIFIC INFORMATION (BACKWARDS)
static void	print_error_msg_reverse(char *msg, char *info)
{
	ft_putstr_fd(MSG_MINISHELL, STDERR_FILENO);
	if (*info == '\0')
		ft_putendl_fd(msg, STDERR_FILENO);
	else
	{
		ft_putstr_fd(info, STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
	}
}

// PRINT ERROR MESSAGE ACCORDING TO ERROR CODE
void	print_error(t_data *ms_data, int error_code, char *error_info)
{
	if (error_code == MALLOC)
		print_error_msg(MSG_MALLOC, "");
	if (error_code == SYNTAX)
		print_error_msg(MSG_SYNTAX, error_info);
	if (error_code == QUOTE)
		print_error_msg_quotes(MSG_QUOTE, error_info);
	if (error_code == ARG_LIMIT)
		print_error_msg_reverse(MSG_ARG_LIMIT, error_info);
	if (error_code == HEREDOC)
		print_error_msg(MSG_HEREDOC, "");
	if (error_code == HEREDOC_CTRL_D)
		print_error_msg_hdoc(MSG_HDOC_CTRLD, error_info);
	if (error_code == FORK)
		print_error_msg_hdoc(MSG_FORK, error_info);
	if (error_code == REDIR_FILE)
		print_error_msg_reverse(MSG_REDIR_FILE, error_info);
	set_return_code(ms_data, error_code);
}

void	print_syntax_error(t_data *ms_data, int token)
{
	if (token == TOKEN_PIPE)
		print_error(ms_data, SYNTAX, "`|\'");
	if (token == TOKEN_INPU)
		print_error(ms_data, SYNTAX, "`<\'");
	if (token == TOKEN_OUTP)
		print_error(ms_data, SYNTAX, "`>\'");
	if (token == TOKEN_DELI)
		print_error(ms_data, SYNTAX, "`<<\'");
	if (token == TOKEN_APPE)
		print_error(ms_data, SYNTAX, "`>>\'");
	if (token == TOKEN_EOF)
		print_error(ms_data, SYNTAX, "`new line\'");
}
