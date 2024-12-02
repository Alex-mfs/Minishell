/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:49:15 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/30 16:08:13 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_cd(t_data *ms_data, char **argv, char *pwd)
{
	int		i;
	int		args_count;

	args_count = ft_count_args(argv);
	if (args_count > 2)
	{
		prepare_error("too many arguments", "cd", ms_data, 1);
		free(pwd);
		return ;
	}
	if (!argv[1])
		i = handle_home(ms_data);
	else if (argv[1][0] == '~')
		i = handle_home(ms_data);
	else if (argv[1][0] == '/')
		i = handle_absolut_path(argv[1], ms_data);
	else
		i = handle_relative_path(argv[1], ms_data);
	if (i == 0)
		update_pwd(pwd, ms_data);
	else
		free(pwd);
}

int	handle_absolut_path(char *line, t_data *ms_data)
{
	if (chdir(line) == -1)
	{
		prepare_cd_error("cd", line, ms_data, errno);
		return (1);
	}
	return (0);
}

int	handle_home(t_data *ms_data)
{
	char	*home;

	home = my_getenv("HOME", ms_data->variables);
	if (home != NULL)
		chdir(home);
	else
	{
		prepare_error("HOME not set", "cd", ms_data, 1);
		free(home);
		return (1);
	}
	free(home);
	return (0);
}

int	ft_count_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}
