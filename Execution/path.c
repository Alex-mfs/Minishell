/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:39:57 by alfreire          #+#    #+#             */
/*   Updated: 2024/10/17 01:40:25 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_absolute_path(char *exe, t_minish *ms)
{
	char	*tmp;
	char	*path;
	int		i;

	if (exe[0] == '\0')
		return (NULL);
	if (access(exe, F_OK) == 0)
		return (ft_strdup(exe));
	i = 0;
	while (ms->path[i])
	{
		tmp = ft_strjoin(ms->path[i], "/");
		path = ft_strjoin(tmp, exe);
		free(tmp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*get_relative_path(char *exe, t_minish *ms)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(ms->cwd, "/");
	path = ft_strjoin(tmp, exe + 2);
	free(tmp);
	if (access(path, F_OK) == 0)
		return (path);
	free(path);
	if (access(exe, F_OK) == 0)
		return (ft_strdup(exe));
	return (NULL);
}

char	*get_executable_path(char *cmd, t_minish *ms)
{
	if (cmd[0] == '.')
		return (get_relative_path(cmd, ms));
	else
		return (get_absolute_path(cmd, ms));
}
