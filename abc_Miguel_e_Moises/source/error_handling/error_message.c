/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:18:20 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/28 15:27:32 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_exec_error(char *error_message, char *command)
{
	ft_putstr_fd("ERROR: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_message, 2);
	ft_putstr_fd("\n", 2);
}

void	handle_exec_errors(char *path, t_data *ms_data)
{
	if (errno == ENOENT)
	{
		print_exec_error("No such file or directory", path);
		ms_data->return_code = 127;
	}
	else if (errno == EISDIR)
	{
		print_exec_error("Is a directory", path);
		ms_data->return_code = 126;
	}
	else if (errno == ENOTDIR)
	{
		print_exec_error("Not a directory", path);
		ms_data->return_code = 126;
	}
	else if (errno == EACCES)
	{
		print_exec_error("Permission denied", path);
		ms_data->return_code = 126;
	}
	else
	{
		print_exec_error(strerror(errno), path);
		ms_data->return_code = 1;
	}
}

void	handle_path_errors(char *path, t_data *ms_data)
{
	if (errno == ENOENT)
	{
		print_exec_error("No such file or directory", path);
		ms_data->return_code = 1;
	}
	else if (errno == EISDIR)
	{
		print_exec_error("Is a directory", path);
		ms_data->return_code = 1;
	}
	else if (errno == ENOTDIR)
	{
		print_exec_error("Not a directory", path);
		ms_data->return_code = 1;
	}
	else if (errno == EACCES)
	{
		print_exec_error("Permission denied", path);
		ms_data->return_code = 1;
	}
	else
	{
		print_exec_error(strerror(errno), path);
		ms_data->return_code = 1;
	}
}
