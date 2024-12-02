/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init_close_03.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:34:04 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/27 16:23:09 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_environment(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

// INITIALIZE STRUCT t_data (MAIN STRUCT)
t_data	*init_minishell(char **envp, int return_code)
{
	t_data	*ms_data;

	ms_data = (t_data *)malloc(sizeof(*ms_data));
	if (ms_data)
	{
		ms_data->prompt = NULL;
		ms_data->input = NULL;
		ms_data->tree = NULL;
		ms_data->lst_nodes = NULL;
		ms_data->return_code = return_code;
		ms_data->heredoc_count = 1;
		ms_data->filename = NULL;
		ms_data->variables = copy_environment(envp);
		ms_data->no_string = false;
	}
	return (ms_data);
}

// DELETE HEREDOC FILES
void	delete_heredoc(void)
{
	DIR				*heredoc_folder;
	struct dirent	*entry;
	char			*filename;

	heredoc_folder = opendir(HEREDOC_FOLDER);
	if (heredoc_folder)
	{
		entry = readdir(heredoc_folder);
		while (entry)
		{
			if (ft_strnstr(entry->d_name, HEREDOC_NAME, \
			sizeof(HEREDOC_NAME) - 1))
			{
				filename = ft_strjoin(HEREDOC_FOLDER, entry->d_name);
				if (filename)
					unlink(filename);
				free(filename);
			}
			entry = readdir(heredoc_folder);
		}
		closedir(heredoc_folder);
	}
}

// DELETE VARIABLES
void	delete_variables(char **variables)
{
	int	i;

	i = 0;
	while (variables[i])
	{
		free(variables[i]);
		i++;
	}
	free(variables);
}

// CLEAN MINISHELL - RESET
void	clean_shell(t_data *ms_data)
{
	free(ms_data->prompt);
	free(ms_data->input);
	ms_data->tree = free_tree(ms_data->tree);
	lst_clean(&(ms_data->lst_nodes));
	delete_heredoc();
	delete_variables(ms_data->variables);
	ms_data->prompt = NULL;
	ms_data->input = NULL;
	ms_data->variables = NULL;
	ms_data->heredoc_count = 1;
	ms_data->no_string = false;
	free(ms_data);
}
