/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/12/03 11:26:37 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sanitize_path(t_minish *ms)
{
	char	*buff_path;

	ft_free_matrix(ms->path);
	buff_path = get_env("PATH", ms->env_tmp);
	if (buff_path)
		ms->path = ft_split(buff_path, ':');
	free(buff_path);
}

void	tk_clear(t_token **lst)
{
	t_token	*buff;

	if (lst)
	{
		while (*lst)
		{
			buff = (*lst)->next;
			free((*lst)->token);
			free(*lst);
			*lst = buff;
		}
	}
}

void	cmd_clear(t_ast **lst)
{
	t_ast	*buff;

	if (lst)
	{
		while (*lst)
		{
			buff = (*lst)->next;
			if ((*lst)->redirections && (*lst)->index >= 0)
				cmd_clear(&((*lst)->redirections));
			if ((*lst)->cmd)
				free((*lst)->cmd);
			if ((*lst)->args)
				ft_free_matrix((*lst)->args);
			free(*lst);
			*lst = buff;
		}
	}
}

void	sanitize_ms(t_minish *ms, bool sair)
{
	if (ms->pipes)
	{
		close_all_pipes(ms);
		ft_free_intmatrix(ms->pipes,
			(size_t)cmdlst_size(ms->cmd_list, false) - 1);
		ms->pipes = NULL;
	}
	if (ms->cmd_list)
		cmd_clear(&(ms->cmd_list));
	if (ms->tk_list)
		tk_clear(&(ms->tk_list));
	reset_values(ms);
	if (sair)
	{
		if (ms->cwd)
			free(ms->cwd);
		if (ms->env_list)
			ft_free_matrix(ms->env_list);
		if (ms->env_list)
			ft_free_matrix(ms->env_tmp);
		if (ms->path)
			ft_free_matrix(ms->path);
		exit(get_exit_status());
	}
}

void	unlink_hd_file(t_minish *ms)
{
	int		i;
	char	*file_name;

	if (ms->hd == 0)
		return ;
	i = ms->hd;
	while (i > 0)
	{
		file_name = create_hd_file(ms, false, i);
		if (access(file_name, F_OK) == -1)
		{
			free(file_name);
			return ;
		}
		unlink(file_name);
		free(file_name);
		i--;
	}
}
