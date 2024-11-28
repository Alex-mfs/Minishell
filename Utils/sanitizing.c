/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/28 18:26:51 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*clear_top_token(t_token *node)
{
	t_token	*tmp;

	tmp = node->next;
	free(node->token);
	free(node);
	return (tmp);
}

void	sanitize_path(t_minish *ms)
{
	char	*buff_path;

	ft_free_matrix(ms->path);
	buff_path = get_env("PATH", ms->env_tmp);
	if (buff_path)
		ms->path = ft_split(buff_path, ':');
	free(buff_path);
}

static void	tk_clear(t_token **lst)
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

static void	cmd_clear(t_ast **lst)
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
