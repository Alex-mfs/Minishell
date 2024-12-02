/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:28:10 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/30 17:19:56 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	prepare_error(char *error_message, char *command, t_data *ms_data, \
int return_code)
{
	print_exec_error(error_message, command);
	ms_data->return_code = return_code;
}

void	prepare_cd_error(char *error_message, char *command, \
t_data *ms_data, int error_code)
{
	(void)error_message;
	if (error_code == ENOENT)
		prepare_error("No such file or directory", command, ms_data, 1);
	else if (error_code == EACCES)
		prepare_error("Permission denied", command, ms_data, 1);
	else
		prepare_error(strerror(error_code), command, ms_data, 1);
}

int	prepare_exit_error(char *error_message, char *arg, \
t_data *ms_data, int exit_code)
{
	ft_putstr_fd("ERROR: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_message, 2);
	ft_putstr_fd("\n", 2);
	ms_data->return_code = exit_code;
	return (exit_code);
}

void	prepare_exit_numeric(char *str, char **argv, t_data *ms_data, \
int return_code)
{
	ft_putstr_fd("ERROR: ", 2);
	ft_putstr_fd(argv[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(argv[1], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	ms_data->return_code = return_code;
}
