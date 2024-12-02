/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:09:31 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/30 18:46:37 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_executable(char *command, t_data *ms_data)
{
	char	*path_env;
	char	*path;
	char	*dir;
	char	full_path[PATH_MAX];

	if (ft_strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		else
			return (NULL);
	}
	path_env = get_path_env(ms_data, command);
	if (!path_env)
		return (ft_strdup(command));
	path = ft_strdup(path_env);
	dir = ft_strtok(path, ":");
	while (dir)
	{
		build_full_path_2(full_path, dir, command);
		if (access(full_path, X_OK) == 0)
			return (check_final_finder(path_env, path, full_path, 0));
		dir = ft_strtok(NULL, ":");
	}
	return (check_final_finder(path_env, path, full_path, -1));
}

void	build_full_path_2(char *full_path, const char *dir, const char *command)
{
	full_path[0] = '\0';
	ft_strcpy(full_path, dir);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, command);
}

char	*get_path_env(t_data *ms_data, char *command)
{
	char	*path_env;

	(void)command;
	path_env = my_getenv("PATH", ms_data->variables);
	if (!path_env)
		return (NULL);
	return (path_env);
}

int	build_full_path(char *full_path, const char *dir, const char *command)
{
	full_path[0] = '\0';
	ft_strcpy(full_path, dir);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, command);
	return (access(full_path, X_OK));
}

char	*check_final_finder(char *path_env, char *path, char *full_path, \
int code)
{
	if (code == 0)
	{
		free(path_env);
		free(path);
		return (ft_strdup(full_path));
	}
	else
	{
		free(path_env);
		free(path);
		return (NULL);
	}
	return (NULL);
}
