/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:25:44 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/30 16:52:18 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_tree(t_data *ms_data, t_exec *exec_cmd, int *status)
{
	pid_t		pid;
	pid_t		parent_pid;
	int			local_status;

	(void)status;
	local_status = 0;
	parent_pid = getpid();
	if (exec_cmd == NULL)
		return ;
	if (exec_cmd->type == EXEC && search_builtin(exec_cmd->argv[0]))
		ft_exec_builtin(exec_cmd->argv, ms_data);
	else
	{
		signal(SIGINT, ignore_child);
		signal(SIGQUIT, ignore_child);
		pid = fork();
		if (pid == 0)
			from_child(ms_data, parent_pid);
		else if (pid > 0)
			from_parent(local_status, ms_data);
	}
}

void	signals_exec_tree(t_data *ms_data, int parent_pid)
{
	signal_child_handler(-1, ms_data, parent_pid);
	signal(SIGINT, (void *)signal_child_handler);
	signal(SIGQUIT, (void *)signal_child_handler);
}

void	from_child(t_data *ms_data, int parent_pid)
{
	signals_exec_tree(ms_data, parent_pid);
	exec_tree(ms_data->tree, ms_data);
	exit(0);
}

void	from_parent(int local_status, t_data *ms_data)
{
	waitpid(-1, &local_status, 0);
	if (WIFEXITED(local_status))
		ms_data->return_code = WEXITSTATUS(local_status);
	else if (WIFSIGNALED(local_status))
		handle_wif(ms_data, &local_status);
}
