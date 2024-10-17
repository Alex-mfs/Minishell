/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:44:12 by alfreire          #+#    #+#             */
/*   Updated: 2024/10/17 01:52:31 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pipe_data_flow(int cmd_index, t_minish *ms)
{
	if (ms->cmd_num <= 1)
		return ;
	if (ms->fd_in == 0 && cmd_index > 0)
		ms->fd_in = ms->pipes[cmd_index - 1][0];
	if (ms->fd_out == 1 && cmd_index < ms->cmd_num - 1)
		ms->fd_out = ms->pipes[cmd_index][1];
}

void	relinking_in_out(t_minish *ms)
{
	if (ms->fd_in != 0)
		dup2(ms->fd_in, 0);
	if (ms->fd_out != 1)
		dup2(ms->fd_out, 1);
}

void	close_in_out(int index, t_minish *ms)
{
	if (ms->fd_in != 0)
		close(ms->fd_in);
	if (ms->fd_out != 1)
		close(ms->fd_out);
	if (index > 0)
		close(ms->pipes[index - 1][0]);
	if (ms->cmd_num - 1 > index)
		close(ms->pipes[index][1]);
	ms->fd_in = 0;
	ms->fd_out = 1;
}

// 	-> Gera uma nova matriz de pipes. 
//A matriz é uma matriz 2D de inteiros, onde cada linha representa um pipe.
//	-> A primeira coluna é o descritor do ficheiro de entrada e a segunda
//coluna é o descritor do ficheiro de saída;
void	pipeline_matrix(t_minish *ms)
{
	int	i;

	i = 0;
	ms->pipes = ft_calloc(ms->cmd_num, sizeof(int *));
	if (!ms->pipes)
		return ;
	while (i < ms->cmd_num - 1)
	{
		ms->pipes[i] = ft_calloc(2, sizeof(int));
		if (!ms->pipes[i])
			return ;
		pipe(ms->pipes[i]);
		i++;
	}
}
