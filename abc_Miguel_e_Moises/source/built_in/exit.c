/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:49:25 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/30 17:18:39 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <limits.h>

void	handle_exit(char **argv, t_data *ms_data, char *pwd)
{
	int		exit_code;
	char	*endptr;
	long	num;

	check_print_exit();
	exit_code = ms_data->return_code;
	if (argv[1])
	{
		num = ft_strtol(argv[1], &endptr);
		if (check_required_args(argv[1], ms_data, num) == 1)
		{
			prepare_exit_numeric("numeric argument required", argv, \
			ms_data, 2);
			prepare_to_exit(ms_data, pwd, 2);
		}
		if (check_arg2(argv, ms_data) == 1)
			return ;
		else
		{
			exit_code = num % 256;
			if (exit_code < 0)
				exit_code = exit_code + 256;
		}
	}
	prepare_to_exit(ms_data, pwd, exit_code);
}

int	check_arg2(char **argv, t_data *ms_data)
{
	int	arg_count;

	if (check_2_in_1(argv[1]) == 1)
	{
		if (ms_data->return_code == 0)
			prepare_error("too many arguments", "exit", ms_data, 1);
		else
			prepare_error("too many arguments", "exit", ms_data, \
			ms_data->return_code);
		return (1);
	}
	arg_count = ft_count_args(argv);
	if (arg_count > 2)
	{
		if (ms_data->return_code == 0)
			prepare_error("too many arguments", "exit", ms_data, 1);
		else
			prepare_error("too many arguments", "exit", ms_data, \
			ms_data->return_code);
		return (1);
	}
	return (0);
}

void	check_print_exit(void)
{
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", STDOUT_FILENO);
}
