/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:44:12 by alfreire          #+#    #+#             */
/*   Updated: 2024/11/06 15:36:33 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pipe_data_flow(int cmd_index, t_minish *ms, char **fullcmd)
{
	int	cmd_num;

	printf("pipe_data_flow: fd_in = %d e fd_out = %d\n", ms->fd_in, ms->fd_out);
	cmd_num = cmdlst_size(ms->cmd_list, false);
	if (cmd_num <= 1)
		return ;
	printf("pipe_data_flow: cmd_index=%d, cmd_num=%d\n", cmd_index, cmd_num);
	if (cmd_index > 0 && ms->fd_in == STDIN_FILENO)
	{
		ms->fd_in = ms->pipes[cmd_index - 1][0];
	}
	if (cmd_index < cmd_num - 1 && ms->fd_out == STDOUT_FILENO)
	{
		if (fullcmd && !get_executable_path(*fullcmd, ms))
			printf("minishell: command not found\n");
		ms->fd_out = ms->pipes[cmd_index][1];
		printf("pipe_data_flow: cmd_index=%d\n", cmd_index);
	}
}

// void	relinking_in_out(t_minish *ms)
// {
// 	if (ms->fd_in != 0)
//     {
//         dup2(ms->fd_in, 0);
// 		close(ms->fd_in);
//     }
// 	if (ms->fd_out != 1)
//     {
//         dup2(ms->fd_out, 1);
// 		close(ms->fd_out);
//     }
// }
void	relinking_in_out(t_minish *ms)
{
    if (ms->fd_in >= STDIN_FILENO)
    {
        printf("relinking_in_out: duplicando fd_in (%d) para STDIN\n", ms->fd_in);
        int t = dup2(ms->fd_in, STDIN_FILENO);
		if (t == -1)
        {
            perror("dup2 fd_in");
            exit(EXIT_FAILURE);
        }
        //close(ms->fd_in);
		//ms->fd_in = STDIN_FILENO;
    }
    if (ms->fd_out >= STDOUT_FILENO)
    {
        printf("relinking_in_out: duplicando fd_out (%d) para STDOUT\n", ms->fd_out);
		int t2 = dup2(ms->fd_out, STDOUT_FILENO);
		if (t2 == -1)
        {
            perror("dup2 fd_out");
            exit(EXIT_FAILURE);
        }
        //close(ms->fd_out);
		//ms->fd_out = STDOUT_FILENO;
    }
	printf("relinking_in_out: após redirecionamento, ms->fd_in=%d, ms->fd_out=%d\n", ms->fd_in, ms->fd_out);
}


void	close_in_out(int index, t_minish *ms)
{
	if (ms->fd_in > STDIN_FILENO)
    {
        close(ms->fd_in);
    }
	if (ms->fd_out > STDOUT_FILENO)
    {
        close(ms->fd_out);
    }
	if (index > 0)
		close(ms->pipes[index - 1][0]);
	if (index != (cmdlst_size(ms->cmd_list, false) - 1))
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
