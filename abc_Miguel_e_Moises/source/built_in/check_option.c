/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_option.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:25:04 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/30 16:09:35 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_options_built_ins(char **argv, t_data *ms_data)
{
	int	checker;

	checker = 0;
	if (ft_strcmp(argv[0], "export") == 0)
		checker = check_options(argv, ms_data);
	else if (ft_strcmp(argv[0], "cd") == 0)
		checker = check_options(argv, ms_data);
	else if (ft_strcmp(argv[0], "echo") == 0)
		checker = check_options_echo(argv, ms_data);
	else if (ft_strcmp(argv[0], "unset") == 0)
		checker = check_options(argv, ms_data);
	else if (ft_strcmp(argv[0], "exit") == 0)
		checker = check_options_exit(argv, ms_data);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		checker = check_options(argv, ms_data);
	else if (ft_strcmp(argv[0], "env") == 0)
		checker = check_options_env(argv, ms_data);
	return (checker);
}

int	check_options_exit(char **argv, t_data *ms_data)
{
	if (!argv[1])
		return (0);
	if (ft_strcmp(argv[1], "--help") == 0)
	{
		prepare_error("Minishell is not build for that my friend", \
		"options", ms_data, 1);
		return (1);
	}
	return (0);
}

int	check_options_env(char **argv, t_data *ms_data)
{
	if (argv[1] == NULL)
		return (0);
	if (ft_strncmp(argv[1], "-", 1) == 0 && ft_is_char(argv[1][1]) == 1)
	{
		prepare_error("Minishell is not build for that my friend", \
		"options", ms_data, 1);
		return (1);
	}
	else if (ft_strcmp(argv[1], "--") == 0 && ft_is_char(argv[1][2]) == 0)
	{
		prepare_error("Minishell is not build for that my friend", \
		"options", ms_data, 1);
		return (1);
	}
	return (0);
}

int	check_options(char **argv, t_data *ms_data)
{
	if (argv[1] == NULL)
		return (0);
	if (ft_strncmp(argv[1], "-", 1) == 0 && ft_is_char(argv[1][1]) == 1)
	{
		prepare_error("Minishell is not build for that my friend", \
		"options", ms_data, 1);
		return (1);
	}
	else if (ft_strcmp(argv[1], "--") == 0 && ft_is_char(argv[1][2]) == 0)
	{
		prepare_error("Minishell is not build for that my friend", \
		"options", ms_data, 1);
		return (1);
	}
	return (0);
}

int	check_options_echo(char **argv, t_data *ms_data)
{
	if (argv[1] == NULL)
		return (0);
	if (ft_strcmp(argv[1], "-e") == 0 || ft_strcmp(argv[1], "-E") == 0)
	{
		prepare_error("Minishell is not build for that my friend", \
		"options", ms_data, 1);
		return (1);
	}
	else if (ft_strcmp(argv[1], "--help") == 0)
	{
		prepare_error("Minishell is not build for that my friend", \
		"options", ms_data, 1);
		return (1);
	}
	else if (ft_strcmp(argv[1], "--version") == 0)
	{
		prepare_error("Minishell is not build for that my friend", \
		"options", ms_data, 1);
		return (1);
	}
	return (0);
}
