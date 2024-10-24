/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/10/23 10:36:42 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*void	ft_free(void *p)
{
	if (p)
		free(p);
	p = NULL;
}

char	*get_env(char *key)
{
	t_env	*tmp;
	t_list	*curr;

	if (key[0] == '$')
		key++;
	curr = ms()->envlist;
	while (curr)
	{
		tmp = (t_env *)curr->content;
		if (!ft_strcmp(tmp->key, key))
			return (ft_strdup(tmp->value));
		curr = curr->next;
	}
	return (ft_strdup(""));
}

void	update_envs(void)
{
	char	*tmp;

	matrix_destroy(ms()->path);
	matrix_destroy(ms()->envp);
	tmp = get_env("PATH");
	(ms()->path) = ft_split(tmp, ':');
	(ms()->envp) = envlist_to_matrix(ms()->envlist);
	free(tmp);
}
*/

void	sanitize_envp(t_minish *ms)
{
	//libertar path?
	//libertar env_list
	//buscar linha PATH, dar split de acordo com ':'
	//voltar a guardar a informacao actualizada em env_list
	(void)ms;
}

static void	tk_clear(t_token **lst)
{
	t_token	*buff;

	if (lst)
	{
		while (*lst)
		{
			buff = (*lst)->next;
			//free((*lst)->token);
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
			if ((*lst)->left && (*lst)->index >= 0)
				cmd_clear(&((*lst)->left));
			if ((*lst)->right && (*lst)->index >= 0)
				cmd_clear(&((*lst)->right));
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
	/*ft_free(ms()->input);
	ft_free(ms()->prompt);
	ast_clear(ms()->ast, ast_destroy_node);
	matrix_destroy(ms()->pipes);
	ft_lstclear(&ms()->lexemes, (void (*)(void *))token_destroy);
	(ms()->ast) = NULL;
	(ms()->pipes) = NULL;
	(ms()->prompt) = NULL;
	(ms()->lexemes) = NULL;
	(ms()->num_commands) = 0;
	if (end)
	{
		ft_free(ms()->cwd);
		matrix_destroy(ms()->path);
		matrix_destroy(ms()->envp);
		ft_lstclear(&ms()->envlist, (void (*)(void *))env_destroy);
		ft_lstclear(&ms()->envtmp, (void (*)(void *))env_destroy);
		exit(ms()->exit_status);
	}*/
	if (ms->pipes)
		ft_free_intmatrix(ms->pipes, (size_t)cmdlst_size(ms->cmd_list, false));
	if (ms->cmd_list)
		cmd_clear(&(ms->cmd_list));
	if (ms->tk_list)
		tk_clear(&(ms->tk_list));
	ms->pipes = NULL;
	ms->cmd_list = NULL;
	ms->tk_list = NULL;
	if (sair)
	{
		if (ms->cwd)
			free(ms->cwd);
		if (ms->env_list)
			ft_free_matrix(ms->env_list);
		exit(get_exit_status());
	}
}
