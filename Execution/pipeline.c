/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:44:12 by alfreire          #+#    #+#             */
/*   Updated: 2024/10/25 13:28:59 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pipe_data_flow(int cmd_index, t_minish *ms)
{
	int	cmd_num;

	cmd_num = cmdlst_size(ms->cmd_list, true);
	if (cmd_num <= 1)
		return ;
	printf("pipe_data_flow: cmd_index=%d, cmd_num=%d\n", cmd_index, cmd_num);
	if (cmd_index > 0)
	{
		ms->fd_in = ms->pipes[cmd_index - 1][0];
	}
	if (cmd_index < cmd_num - 1)
	{
		ms->fd_out = ms->pipes[cmd_index][1];
	}
}

void	relinking_in_out(t_minish *ms)
{
	if (ms->fd_in != 0)
    {
        dup2(ms->fd_in, 0);
		close(ms->fd_in);
    }
	if (ms->fd_out != 1)
    {
        dup2(ms->fd_out, 1);
		close(ms->fd_out);
    }
}

void	close_in_out(int index, t_minish *ms)
{
	if (ms->fd_in != 0)
    {
        close(ms->fd_in);
    }
	if (ms->fd_out != 1)
    {
        close(ms->fd_out);
    }
	if (index == -1) // Sinaliza o fechamento final de todos os pipes
	{
		for (int i = 0; i < cmdlst_size(ms->cmd_list, true) - 1; i++)
		{
			close(ms->pipes[i][0]);
			close(ms->pipes[i][1]);
		}
	}
	else
	{
		// Fecha os pipes relacionados ao índice atual
		if (index > 0)
			close(ms->pipes[index - 1][0]);
		if ((cmdlst_size(ms->cmd_list, true) - 1) > index)
			close(ms->pipes[index][1]);
	}
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
	ms->pipes = ft_calloc(cmdlst_size(ms->cmd_list, true) - 1, sizeof(int *));
	if (!ms->pipes)
		return ;
	while (i < (cmdlst_size(ms->cmd_list, true) - 1))
	{
		ms->pipes[i] = ft_calloc(2, sizeof(int));
		if (!ms->pipes[i])
			return ;
		pipe(ms->pipes[i]);
		i++;
	}
}
