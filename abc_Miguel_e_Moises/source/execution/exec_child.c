/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:18:15 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/27 17:23:19 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_tree(t_cmd *tree, t_data *ms_data)
{
	t_exec	*exec_cmd;
	t_pipe	*pipe_cmd;
	int		exit_code;

	if (!tree)
	{
		exit_code = ms_data->return_code;
		clean_shell(ms_data);
		exit(exit_code);
	}
	if (tree->type == EXEC)
	{
		exec_cmd = (t_exec *)tree;
		case_exec(exec_cmd, ms_data);
	}
	else if (tree->type == REDI)
	{
		case_redir(tree, ms_data);
	}
	else if (tree->type == PIPE)
	{
		pipe_cmd = (t_pipe *)tree;
		case_pipe(pipe_cmd, ms_data);
	}
}

void	case_redir(t_cmd *tree, t_data *ms_data)
{
	int		fd;
	int		return_code;
	t_redir	*redir_cmd;

	redir_cmd = (t_redir *)tree;
	fd = open(redir_cmd->file, redir_cmd->mode, 0644);
	if (fd == -1)
	{
		handle_path_errors(redir_cmd->file, ms_data);
		return_code = ms_data->return_code;
		clean_shell(ms_data);
		exit(return_code);
	}
	if (dup2(fd, redir_cmd->fd) == -1)
	{
		print_exec_error(strerror(errno), "dup2");
		return_code = ms_data->return_code;
		clean_shell(ms_data);
		exit(return_code);
	}
	close(fd);
	exec_tree(redir_cmd->cmd, ms_data);
}
