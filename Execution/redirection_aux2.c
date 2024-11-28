/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_aux2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:56:02 by alfreire          #+#    #+#             */
/*   Updated: 2024/11/28 22:03:53 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	open_file(char *file)
{
	int	fd;

	if (!file)
		return (false);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}

char	*create_hd_file(int i, bool flag)
{
	char	*file;
	char	*nbr;
	char	*temp;

	file = NULL;
	nbr = ft_itoa(i);
	temp = ft_strjoin("heredoc", nbr);
	file = ft_strjoin(temp, ".temp");
	free(nbr);
	free(temp);
	if (flag)
	{
		if (!open_file (file))
		{
			free(file);
			return (NULL);
		}
	}
	return (file);
}

void	hd_sanitize(t_minish *ms, int e_code)
{
	if (!ms)
		exit(1);
	if (ms->pipes)
		ft_free_intmatrix(ms->pipes,
			(size_t)cmdlst_size(ms->cmd_list, false) - 1);
	if (ms->cmd_list)
		cmd_clear(&(ms->cmd_list));
	if (ms->tk_list)
		tk_clear(&(ms->tk_list));
	ms->pipes = NULL;
	ms->cmd_list = NULL;
	ms->tk_list = NULL;
	ms->aux_merge = false;
	ms->dont_execve = false;
	if (ms->cwd)
		free(ms->cwd);
	if (ms->env_list)
		ft_free_matrix(ms->env_list);
	if (ms->env_list)
		ft_free_matrix(ms->env_tmp);
	if (ms->path)
		ft_free_matrix(ms->path);
	rl_clear_history();
	exit(e_code);
}
