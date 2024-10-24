/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:56:02 by alfreire          #+#    #+#             */
/*   Updated: 2024/10/23 01:49:25 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_key(char *str)
{
	char	*tmp;
	int		len;

	len = 0;
	tmp = ft_strnstr(str, "$", ft_strlen(str));
	if (tmp[1] == '?')
		return (ft_strdup("$?"));
	while (ft_isalnum(tmp[len + 1]) || tmp[len + 1] == '_')
		len++;
	return (ft_substr(tmp, 0, len + 1));
}

char	*replace_substring(char *str, char *old, char *new)
{
	char	*ret;
	char	*tmp;
	char	*ptr;
	int		len;

	if (!str || !old || !new)
		return (NULL);
	len = ft_strlen(str) + ft_strlen(new) - ft_strlen(old);
	ret = ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	ptr = ft_strnstr(str, old, ft_strlen(str));
	if (!ptr)
		return (NULL);
	tmp = ft_substr(str, 0, ptr - str);
	ft_strlcat(ret, tmp, len + 1);
	ft_strlcat(ret, new, len + 1);
	ft_strlcat(ret, ptr + ft_strlen(old), len + 1);
	free(tmp);
	return (ret);
}

char	*expand_heredoc(char *line, char **env_list)
{
	char	*result;
	char	*value;
	char	*key;
	char	*tmp;

	result = ft_strdup(line);
	while (ft_strnstr(result, "$", ft_strlen(result)))
	{
		key = find_key(result);
		if (ft_str_cmp(key, "$?"))
			value = ft_itoa(get_exit_status());
		else
			value = get_env(key, env_list);
		tmp = result;
		result = replace_substring(result, key, value);
		free(tmp);
		free(value);
		free(key);
	}
	free(line);
	return (result);
}

void	read_until_delimiter(const char *delimiter, t_minish *ms)
{
	int		fd;
	char	*line;

	fd = open("heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	while (1)
	{
		line = readline("heredoc > ");
		if (!line)
		{
			printf("\n");
			break ;
		}
		else if (ft_str_cmp(line, delimiter))
		{
			free(line);
			break ;
		}
		line = expand_heredoc(line, ms->env_list);
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	sanitize_ms(ms, true);
}

int	heredoc(char *delimiter, t_minish *ms)
{
	int		fd;
	int		status;
	pid_t	pid;

	set_signals_heredoc();
	if (ms->fd_in > STDIN_FILENO)
		close(ms->fd_in);
	pid = fork();
	if (pid == 0)
	{
		set_signals_heredoc();
		read_until_delimiter(delimiter, ms);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		sanitize_ms(ms, true);
		return (-1);
	}
	set_signals();
	fd = open("heredoc.tmp", O_RDONLY);
	if (fd == -1)
		error("minishell: heredoc\n", 1);
	return (fd);
}

void	execute_redir(const char *type, char *filename, t_minish *ms)
{
	int	fd;	

	fd = -1;
	if (ft_str_cmp(type, ">"))
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (ft_str_cmp(type, ">>"))
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (ft_str_cmp(type, "<"))
		fd = open(filename, O_RDONLY);
	else if (ft_str_cmp(type, "<<"))
		fd = heredoc(filename, ms);
	if (fd == -1)
	{
		perror(filename);
		set_exit_status(1);
		return ;
	}
	if (ft_str_cmp(type, "<") || ft_str_cmp(type, "<<"))
		ms->fd_in = fd;
	else
		ms->fd_out = fd;
}
