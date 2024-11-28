/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:56:02 by alfreire          #+#    #+#             */
/*   Updated: 2024/11/28 20:45:03 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	open_file(char *file)
{
	int	fd;

	if (!file)
		return (false);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}

char	*create_hd_file(int i, bool flag)
{
	char	*file;
	char	*nbr;
	char	*temp;

	file = NULL;
	nbr = ft_itoa(i);
	temp = ft_strjoin("heredoc", nbr);
	file = ft_strjoin(temp, ".temp");
	free(nbr);
	free(temp);
	if (flag)
	{
		if (!open_file (file))
		{
			free(file);
			return (NULL);
		}
	}
	return (file);
}

void	hd_sanitize(t_minish *ms, int e_code)
{
	if (!ms)
		exit(1);
	if (ms->pipes)
		ft_free_intmatrix(ms->pipes,
			(size_t)cmdlst_size(ms->cmd_list, false) - 1);
	if (ms->cmd_list)
		cmd_clear(&(ms->cmd_list));
	if (ms->tk_list)
		tk_clear(&(ms->tk_list));
	ms->pipes = NULL;
	ms->cmd_list = NULL;
	ms->tk_list = NULL;
	ms->aux_merge = false;
	ms->dont_execve = false;
	if (ms->cwd)
			free(ms->cwd);
	if (ms->env_list)
			ft_free_matrix(ms->env_list);
	if (ms->env_list)
			ft_free_matrix(ms->env_tmp);
	if (ms->path)
		ft_free_matrix(ms->path);
	free(ms);
	rl_clear_history();
	exit(e_code);
}

int	heredoc(char *delimiter, t_minish *ms, bool flag)
{
	int		status;
	pid_t	pid;
	char	*hd_file;
	int		fd;

	ms->hd++;
	sig_ignore();
	hd_file = create_hd_file(ms->hd, true);
	if (!hd_file)
		hd_sanitize(ms, 1);
	pid = fork();
	if (pid == -1)
    {
        perror("fork");
        free(hd_file);
        return (-1);
    }
	if (pid == 0)
	{
		//rl_catch_signals = 0;
		handle_hd_int(-1, ms, delimiter, hd_file);
		signal(SIGINT, (void *)handle_hd_int);
		signal(SIGTERM, (void *)handle_hd_int);
		read_until_deli(delimiter, ms, hd_file, flag);
		hd_sanitize(ms, 0);
	}
	waitpid(pid, &status, 0);
	set_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		set_exit_status(130);
		//write(1, "aqui1\n", 6);
		free(hd_file);
		return (-1);
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) == SIGINT)
	{
		//write(1, "aqui\n", 5);
        set_exit_status(WEXITSTATUS(status));
        free(hd_file);
        return (-1);
	}
	fd = open(hd_file, O_RDONLY);
    if (fd == -1) {
        //write(0, "teste0\n", 7);
		set_exit_status(130);
		//error("minishell: heredoc open failed\n", 1);
        free(hd_file);
        return -1;
    }
    free(hd_file); // Free the hd_file string
    return fd; 
	//return (ms->hd);
}

static void	report_error(char *filename, t_minish *ms)
{
	ms->dont_execve = true;
	if (get_exit_status() != 130)
	{
		if (errno != 0)
			perror(filename);
		else
			error(filename, 2);
		set_exit_status(1);
	}
	return ;
}

int	do_heredoc(char *delimiter, t_minish *ms)
{
	bool	flag;

	flag = false;
	if (ft_strchr(delimiter, '"') || ft_strchr(delimiter, '\''))
		flag = true;
	return (heredoc(delimiter, ms, flag));
}

// int	do_heredoc(const char *delimiter, t_minish *ms)
// {
// 	int		fd;
// 	int		status;
// 	pid_t	pid;

// 	signal(SIGINT, SIG_IGN);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		signal(SIGINT, handle_hd_int);
// 		signal(SIGQUIT, SIG_DFL);
// 		read_until_deli(delimiter, ms);
// 		set_exit_status(0);
// 		sanitize_ms(ms, true);
// 	}
// 	waitpid(pid, &status, 0);
// 	set_signals();
// 	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
// 		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
// 	{
// 		set_exit_status(130);
// 		return (-1);
// 	}
// 	fd = open("heredoc.tmp", O_RDONLY);
// 	if (fd == -1)
// 		error("minishell: heredoc\n", 1);
// 	return (fd);
// }

void    execute_redir(const char *type, char *filename, t_minish *ms)
{
    int fd;

    if (type[0] == '>')
    {
        if (type[1] == '>')
            fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
        else
            fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (fd == -1)
            return (report_error(filename, ms));
        if (ms->fd_out != STDOUT_FILENO)
            close(ms->fd_out);
        ms->fd_out = fd;
    }
    else if (ft_str_cmp(type, "<"))
    {
        fd = open(filename, O_RDONLY);
        if (fd == -1)
            return (report_error(filename, ms));
        if (ms->fd_in != STDIN_FILENO)
            close(ms->fd_in);
        ms->fd_in = fd;
    }
    else if (ft_str_cmp(type, "<<"))
    {
        fd = do_heredoc(filename, ms);
        if (fd == -1)
		{
				ms->dont_execve = true;
				return ;
		}
        if (ms->fd_in != STDIN_FILENO)
            close(ms->fd_in);
        ms->fd_in = fd;
    }
}
