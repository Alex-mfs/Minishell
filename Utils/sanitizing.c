/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/10/16 16:24:27 by joao-rib         ###   ########.fr       */
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
			free((*lst)->token);
			free(*lst);
			*lst = buff;
		}
	}
}

static void	ast_clear(t_ast **lst)
{
	t_ast	*buff;

	if (lst)
	{
		while (*lst)
		{
			buff = (*lst)->next;
			free((*lst)->cmd);
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
	ast_clear(&(ms->cmd_list));
	//WIP free ms->pipes INTMATRIX
	tk_clear(&(ms->tk_list));
	ms->cmd_list = NULL;
	ms->pipes = NULL;
	ms->tk_list = NULL;
	ms->fd_in = 0;
	ms->fd_out = 1;
	if (sair)
	{
		free(ms->cwd);
		ft_free_matrix(ms->env_list);
	}
}
