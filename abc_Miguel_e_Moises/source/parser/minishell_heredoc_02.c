/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_heredoc_02.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:34:31 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/26 11:45:14 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// CREATE FILENAME FOR NEXT HEREDOC FILE
static char	*heredoc_filename(t_data *ms_data)
{
	char	*filename0;
	char	*filename1;
	char	*index;

	if (ms_data->heredoc_count > HEREDOC_LIMIT)
	{
		print_error(ms_data, HEREDOC, "");
		return (NULL);
	}
	index = check_str(ms_data, ft_itoa(ms_data->heredoc_count));
	if (index)
	{
		filename0 = check_str(ms_data, ft_strjoin(HEREDOC_FILE, index));
		free(index);
		if (!filename0)
			return (NULL);
		filename1 = check_str(ms_data, ft_strjoin(filename0, HEREDOC_EXTEN));
		free(filename0);
		return (filename1);
	}
	return (NULL);
}

// CREATE HEREDOC FILES AND WRITE IN THEM
static char	*heredoc_file(t_data *ms_data, char *delimiter)
{
	int		fd;
	char	*filename;

	filename = heredoc_filename(ms_data);
	if (!filename)
		return (NULL);
	fd = check_fd(ms_data, open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0664));
	if (fd == -1)
	{
		filename = free_str(filename);
		return (NULL);
	}
	ms_data->heredoc_count++;
	ms_data->filename = filename;
	if (write_heredoc(ms_data, delimiter, fd) == EXIT_FAILURE)
	{
		filename = free_str(filename);
		close(fd);
		return (NULL);
	}
	ms_data->return_code = 0;
	free(delimiter);
	close(fd);
	return (filename);
}

// CREATE HEREDOC REDIRECTION NODE
t_cmd	*heredoc_node(t_data *ms_data, t_cmd *node, char *delimiter)
{
	char	*heredoc_name;
	t_file	*file;

	ms_data->tree = node;
	heredoc_name = heredoc_file(ms_data, delimiter);
	if (!heredoc_name)
	{
		free(delimiter);
		return (free_tree(node));
	}
	file = check_file(ms_data, (t_file *)malloc(sizeof(*file)));
	if (!file)
	{
		free(heredoc_name);
		return (free_tree(node));
	}
	ft_memset(file, 0, sizeof(*file));
	file->file = heredoc_name;
	file->mode = O_RDONLY;
	file->fd = STDIN_FILENO;
	node = seq_redir(ms_data, node, file);
	if (!node)
		free(heredoc_name);
	free(file);
	return (node);
}
