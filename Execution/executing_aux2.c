/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_aux2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:56:02 by alfreire          #+#    #+#             */
/*   Updated: 2024/11/29 00:18:08 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*which_error(char *bef, char *mid, char *aft)
{
	char	*str;
	char	*tmp;

	str = ft_strjoin(bef, mid);
	tmp = str;
	str = ft_strjoin(tmp, aft);
	free(tmp);
	return (str);
}

void	deal_with_isdir(t_minish *ms, char **arg, char *path)
{
	char	*str;

	str = which_error("minishell: ", *arg, ": Is a directory\n");
	ft_free_matrix(arg);
	free(path);
	error(str, 126);
	free(str);
	sanitize_ms(ms, true);
}

bool	is_builtin(char *command)
{
	return (!ft_strncmp(command, "exit", ft_strlen(command)) || \
	!ft_strncmp(command, "pwd", ft_strlen(command)) || \
	!ft_strncmp(command, "env", ft_strlen(command)) || \
	!ft_strncmp(command, "echo", ft_strlen(command)) || \
	!ft_strncmp(command, "unset", ft_strlen(command)) || \
	!ft_strncmp(command, "export", ft_strlen(command)) || \
	!ft_strncmp(command, "cd", ft_strlen(command)));
}

char	**join_cmd_arg(char	*cmd, char **args)
{
	int		i;
	int		args_count;
	char	**full_cmd;

	args_count = 0;
	while (args[args_count] && args[args_count][0])
		args_count++;
	full_cmd = malloc(sizeof(char *) * (args_count + 2));
	if (!full_cmd)
		return (NULL);
	full_cmd[0] = ft_strdup(cmd);
	i = 0;
	while (i < args_count)
	{
		full_cmd[i + 1] = ft_strdup(args[i]);
		i++;
	}
	full_cmd[i + 1] = NULL;
	return (full_cmd);
}

void	create_fullcmd_pipe_flow(t_minish *ms, t_ast *node)
{
	char	**fullcmd;

	fullcmd = join_cmd_arg(node->cmd, node->args);
	pipe_data_flow(node->index, ms, fullcmd);
	ft_free_matrix(fullcmd);
}
