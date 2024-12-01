/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:44:12 by alfreire          #+#    #+#             */
/*   Updated: 2024/12/01 17:46:23 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pipe_data_flow(int cmd_index, t_minish *ms)
{
	int	cmd_num;

	cmd_num = cmdlst_size(ms->cmd_list, false);
	if (cmd_num <= 1)
		return ;
	if (cmd_index > 0 && ms->fd_in == STDIN_FILENO)
		ms->fd_in = ms->pipes[cmd_index - 1][0];
	if (cmd_index < cmd_num - 1 && ms->fd_out == STDOUT_FILENO)
		ms->fd_out = ms->pipes[cmd_index][1];
}

void	relinking_in_out(t_minish *ms)
{
	if (ms->fd_in != STDIN_FILENO)
	{
		if (dup2(ms->fd_in, STDIN_FILENO) == -1)
		{
			error("errror: dup2 fd_in\n", 1);
			sanitize_ms(ms, true);
		}
		close(ms->fd_in);
	}
	//printf("fd_out=%d, std_out=%d\n", ms->fd_out, STDOUT_FILENO);
	if (ms->fd_out != STDOUT_FILENO)
	{
		//ft_putstr_fd("TestOut1\n", 2);
		if (dup2(ms->fd_out, STDOUT_FILENO) == -1)
		{
			error("error: dup2 fd_out\n", 1);
			sanitize_ms(ms, true);
		}
		//ft_putstr_fd("TestOut2\n", 2);
		close(ms->fd_out);
		//ft_putstr_fd("TestOut3\n", 2);
	}
}

void	close_in_out(int index, t_minish *ms)
{
	if (ms->fd_in > STDIN_FILENO)
		close(ms->fd_in);
	if (ms->fd_out > STDOUT_FILENO)
		close(ms->fd_out);
	if (index > 0)
		close(ms->pipes[index - 1][0]);
	if (index != (cmdlst_size(ms->cmd_list, false) - 1))
		close(ms->pipes[index][1]);
	ms->fd_in = 0;
	ms->fd_out = 1;
}

void	count_pipes(t_minish *ms)
{
	t_token	*aux;

	aux = ms->tk_list;
	while (aux)
	{
		if (aux->type == PIPE)
			ms->qtd_pipes++;
		aux = aux->next;
	}
}

void	pipeline_matrix(t_minish *ms)
{
	int	i;

	i = 0;
	count_pipes(ms);
	if (cmdlst_size(ms->cmd_list, false) <= 1)
		return ;
	ms->pipes = ft_calloc(cmdlst_size(ms->cmd_list, false) - 1, sizeof(int *));
	if (!ms->pipes)
		return ;
	while (i < (cmdlst_size(ms->cmd_list, false) - 1))
	{
		ms->pipes[i] = ft_calloc(2, sizeof(int));
		if (!ms->pipes[i])
			return ;
		pipe(ms->pipes[i]);
		i++;
	}
}
