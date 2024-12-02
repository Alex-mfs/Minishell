/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_check_error_02.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:16:45 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/27 02:44:19 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// PRINT ERROR IF FILE STRUCT WAS NOT CREATED
t_file	*check_file(t_data *ms_data, t_file *file)
{
	if (!file)
		print_error(ms_data, MALLOC, "");
	return (file);
}

// PRINT ERROR IF ARGV IS TOO LONG
int	check_argv(t_data *ms_data, char **argv, int argc)
{
	size_t	size;
	int		i;

	size = sizeof(argv);
	if (argc > 0)
	{
		size = size + (argc + 1) * sizeof(*argv);
		i = 0;
		while (argv[i])
		{
			size = size + (ft_strlen(argv[i]) + 1) * sizeof(*argv[i]);
			i++;
		}
		if (size > ARG_MAX)
		{
			print_error(ms_data, ARG_LIMIT, argv[0]);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

// PRINT ERROR IF FORK FAILED TO CREATE CHILD PROCESS
pid_t	check_fork(t_data *ms_data, pid_t pid)
{
	if (pid == -1)
		print_error(ms_data, FORK, "");
	return (pid);
}

// PRINT ERROR IF REDIRECTED FILENAME IS A VARIABLE THAT EXPANDED TO NOTHING
char	*check_red(t_data *ms_data, char *stoken, char *str)
{
	if (!stoken)
		str = free_str(str);
	else if (*str == '\0' && ms_data->no_string == true)
	{
		ms_data->no_string = false;
		print_error(ms_data, REDIR_FILE, stoken);
		stoken = free_str(stoken);
		str = free_str(str);
	}
	else
		free(stoken);
	return (str);
}
