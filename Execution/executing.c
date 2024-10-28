/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/10/28 17:05:08 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	exec_if_exists(char **arg, t_minish *ms)
// {
// 	char		*path;
// 	struct stat	path_stat;

// 	printf("Executando comando: %s\n", *arg);
// 	path = get_executable_path(*arg, ms);
// 	if (!path || stat(path, &path_stat) != 0)
// 	{
// 		error("minishell: command not found\n", 127);
// 		exit(127);
// 	}
// 	else if (path && stat(path, &path_stat) == 0)
// 	{
// 		if (S_ISDIR(path_stat.st_mode))
// 			error("minishell: is a directory\n", 126);
// 		else if (S_ISREG(path_stat.st_mode))
// 		{
// 			execve(path, arg, ms->env_list);
// 			error("minishell: permission denied or execution failed\n", 126);
// 		}
// 		free(path);
// 		path = NULL;
// 	}
// 	else
// 		error("minishell: command not found\n", 127);
// 	return ;
// }

void	exec_if_exists(char **arg, t_minish *ms)
{
    char *path;
    struct stat path_stat;

	//printf("exec_if_exists: buscando executável para '%s'\n", arg[0]);
    path = get_executable_path(*arg, ms);

    if (!path || stat(path, &path_stat) != 0)
    {
        error("minishell: command not found\n", 127);
        exit(127);
    }
    if (S_ISDIR(path_stat.st_mode))
    {
        error("minishell: is a directory\n", 126);
        exit(126);
    }
	//printf("exec_if_exists: executando '%s'\n", path);

    execve(path, arg, ms->env_list);
    error("minishell: permission denied or execution failed\n", 126);
    exit(126);
}

bool	is_builtin(char *command)
{
	return (!ft_strncmp(command, "exit", ft_strlen(command)) || \
	!ft_strncmp(command, "pwd", ft_strlen(command)) || \
	!ft_strncmp(command, "env", ft_strlen(command)) || \
	!ft_strncmp(command, "echo", ft_strlen(command)) || \
	!ft_strncmp(command, "unset", ft_strlen(command)) || \
	!ft_strncmp(command, "export", ft_strlen(command)) || \
	!ft_strncmp(command, "cd", ft_strlen(command)));
}

char	**join_cmd_arg(char	*cmd, char **args)
{
	int		i;
	int		args_count;
	char	**full_cmd;


	args_count = 0;
	while (args[args_count])
		args_count++;
	full_cmd = malloc(sizeof(char *) * (args_count + 2));
	if (!full_cmd)
		return (NULL);
	full_cmd[0] = ft_strdup(cmd);
	i = 0;
	while (i < args_count)
	{
		full_cmd[i + 1] = ft_strdup(args[i]);
		i++;
	}
	full_cmd[i + 1] = NULL;
	return (full_cmd);
}

// void	do_command(char	*cmd, char **args, t_minish *ms)
// {
// 	char	**full_cmd;

// 	//printf("do_command: cmd = %s\n", cmd);
// 	set_exit_status(0);
// 	if (!is_builtin(cmd))
// 	{
// 		//printf("do_command: '%s' não é builtin, chamando exec_if_exists\n", cmd);
// 		full_cmd = join_cmd_arg(cmd, args);
// 		exec_if_exists(full_cmd, ms);
// 	}
// 	if (ft_str_cmp(cmd, "pwd"))
// 		printf("%s\n", ms->cwd);
// 	else if (ft_str_cmp(cmd, "echo"))
// 		echo(args);
// 	else if (ft_str_cmp(cmd, "exit"))
// 		exit_bash(args, ms);
// 	else if (ft_str_cmp(cmd, "env"))
// 		env(args, ms->env_list);
// 	else if (ft_str_cmp(cmd, "export"))
// 		ft_export(args, ms);
// 	else if (ft_str_cmp(cmd, "unset"))
// 		unset(args, ms);
// 	else if (ft_str_cmp(cmd, "cd"))
// 		cd(args, ms);
// }

void do_command(char *cmd, char **args, t_minish *ms)
{
	//printf("do_command: executando comando '%s'\n", cmd);
    if (!is_builtin(cmd))
    {
        char **full_cmd = join_cmd_arg(cmd, args);
		//printf("do_command: não é builtin, executando '%s'\n", full_cmd[0]);
        exec_if_exists(full_cmd, ms);
        // Se execve falhar, exibir erro e sair
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else
    {
		printf("do_command: é um comando builtin\n");
        // Executar comandos built-in
        if (ft_str_cmp(cmd, "pwd"))
            printf("%s\n", ms->cwd);
        else if (ft_str_cmp(cmd, "echo"))
            echo(args);
        else if (ft_str_cmp(cmd, "exit"))
            exit_bash(args, ms);
        else if (ft_str_cmp(cmd, "env"))
            env(args, ms->env_list);
        else if (ft_str_cmp(cmd, "export"))
            ft_export(args, ms);
        else if (ft_str_cmp(cmd, "unset"))
            unset(args, ms);
        else if (ft_str_cmp(cmd, "cd"))
            cd(args, ms);
    }
}

// pid_t	child_exec(t_ast *node, t_minish *ms)
// {
// 	pid_t	pid;

// 	treat_child_signal();
// 	//printf("child_exec: antes de fork para '%s'\n", node->cmd);
// 	pid = fork();
// 	if (pid == -1)
// 	{
//         printf("minishell: erro %d\n", pid);
//         return pid;  // Retorna -1 para indicar falha no fork
//     }
// 	if (pid == 0)
// 	{
// 		//printf("child_exec: antes de if fdin ou fdout = -1 em '%s'\n", node->cmd);
// 		if (ms->fd_in == -1 || ms->fd_out == -1)
// 			sanitize_ms(ms, true);
// 		//printf("child_exec: chamando pipe_data_flow em '%s'\n", node->cmd);
// 		if (!is_builtin(node->cmd))
// 			pipe_data_flow(node->index, ms, join_cmd_arg(node->cmd, node->args));
// 		else
// 			pipe_data_flow(node->index, ms, NULL);
// 		//printf("child_exec: chamando relinking_in_out para '%s'\n", node->cmd);
// 		relinking_in_out(ms);
// 		//printf("child_exec: executando do_command para '%s'\n", node->cmd);
// 		close_in_out(-1, ms);
// 		do_command(node->cmd, node->args, ms);
// 		set_exit_status(0);
// 		sanitize_ms(ms, true);
// 	}
// 	return (pid);
// }
//////////////
//////////////// estava usando A DEBAIXO!!!!!! /////////
//////////////////
/////////
// pid_t child_exec(t_ast *node, t_minish *ms)
// {
//     pid_t pid;

//     treat_child_signal();
//     pid = fork();
//     if (pid == -1)
//     {
//         perror("minishell: erro ao criar processo filho");
//         return -1;
//     }
//     if (pid == 0)
//     {
//         // Processar redirecionamentos
// 	printf("child_exec: processo filho iniciado para '%s'\n", node->cmd);
//         if (node->left)
// 		{
// 			printf("child_exec: processando redirecionamento de entrada\n");
// 			execute_redir(node->left->cmd, node->left->args[0], ms);
// 		}
//         if (node->right)
// 		{
// 			printf("child_exec: processando redirecionamento de saída\n");
// 			execute_redir(node->right->cmd, node->right->args[0], ms);
// 		}
// 		//printf("child_exec: ms->fd_in=%d, ms->fd_out=%d antes de relinking_in_out\n", ms->fd_in, ms->fd_out);
//         if (ms->fd_in == -1 || ms->fd_out == -1)
//             exit(EXIT_FAILURE);

//         // Configurar fluxo de dados dos pipes
//         pipe_data_flow(node->index, ms, NULL);

//         // Aplicar redirecionamentos
//         relinking_in_out(ms);
// 		//printf("child_exec: ms->fd_in=%d, ms->fd_out=%d após relinking_in_out\n", ms->fd_in, ms->fd_out);
//         // Fechar descritores desnecessários
//         close_in_out(-1, ms);

//         // Executar o comando
//         do_command(node->cmd, node->args, ms);
//         exit(EXIT_SUCCESS);
//     }
//     return pid;
// }
//		///		///	/	/	/		/	/	/	/	/	/	/
//				estava assom antes como embaixo 
//	//		/		//	///	//	/		//	/	/	/	//	
// pid_t child_exec(t_ast *node, t_minish *ms)
// {
//     pid_t pid;
//     t_redir *redir;

//     pid = fork();
//     if (pid == -1)
//     {
//         perror("Erro ao criar processo filho");
//         return -1;
//     }
//     if (pid == 0)
//     {
//         // Processar todos os redirecionamentos
//         redir = node->redirs;
//         while (redir)
//         {
//             printf("child_exec: processando redirecionamento '%s' para '%s'\n", redir->type, redir->filename);
//             execute_redir(redir->type, redir->filename, ms);
//             if (ms->fd_in == -1 || ms->fd_out == -1)
//                 exit(EXIT_FAILURE);
//             redir = redir->next;
//         }

//         // Configurar fluxo de dados dos pipes
//         pipe_data_flow(node->index, ms, NULL);

//         // Aplicar redirecionamentos
//         relinking_in_out(ms);

//         // Fechar descritores desnecessários
//         close_in_out(-1, ms);

//         // Executar o comando
//         do_command(node->cmd, node->args, ms);
//         exit(EXIT_SUCCESS);
//     }
//     return pid;
// }

// pid_t	pipeline_exec(t_ast	*node, t_minish *ms)
// {
// 	pid_t	last_child_pid;

// 	last_child_pid = 0;
// 	if (!node)
// 		return (last_child_pid);
// 	printf("pipeline_exec: node->cmd=%s, node->index=%d\n", node->cmd, node->index);
// 	last_child_pid = pipeline_exec(node->left, ms);
// 	last_child_pid = pipeline_exec(node->right, ms);
// 	if (!is_redir_or_pipe(node->cmd))
// 	{
// 		if (need2be_parent(node->cmd, node->args[0]))
//         {
//             printf("Executing built-in command in parent: %s\n", node->cmd);
//             do_command(node->cmd, node->args, ms);
//         }
// 		else
//         {
//             printf("Executing command in child: %s\n", node->cmd);
//             last_child_pid = child_exec(node, ms);
//         }
// 	}
// 	else if (is_redirection(node->cmd))
//     {
//         printf("Executing redirection: %s\n", node->cmd);
//         execute_redir(node->cmd, node->args[0], ms);
//     }
// 	return (last_child_pid);
// }

pid_t child_exec(t_ast *node, t_minish *ms)
{
    pid_t pid;
    t_redir *redir;

    pid = fork();
    if (pid == -1)
    {
        perror("Erro ao criar processo filho");
        return -1;
    }	
    if (pid == 0)
    {
        // Processa redirecionamentos do comando atual
        redir = node->redirs;
        while (redir)
        {
            printf("child_exec: processando redirecionamento '%s' para '%s'\n", redir->type, redir->filename);
			execute_redir(redir->type, redir->filename, ms);
            redir = redir->next;
        }
        // Configura fluxo de dados dos pipes se não houver redirecionamento
        pipe_data_flow(node->index, ms, NULL);
        relinking_in_out(ms);

        close_in_out(-1, ms);
        do_command(node->cmd, node->args, ms);
        exit(EXIT_SUCCESS);
    }
    return pid;
}

pid_t	pipeline_exec(t_ast *cmd_list ,t_minish *ms)
{
	t_ast	*current;
	pid_t	last_child_pid;

	current = cmd_list;
	last_child_pid = 0;
	while (current)
	{
		//printf("pipeline_exec: executando comando '%s'\n", current->cmd);
		if (!is_redir_or_pipe(current->cmd))
		{
			if (need2be_parent(current->cmd, current->args[0]))
				do_command(current->cmd, current->args, ms);
			else
			{
				last_child_pid = child_exec(current, ms);
				close_in_out(current->index, ms);
			}
		}
		// else if (is_redirection(current->cmd))
		// 	execute_redir(current->cmd, current->args[0], ms);
		current = current->next;
	}
	return (last_child_pid);
}

// void	execute(t_minish *ms)
// {
// 	int		status;
// 	pid_t	last_child_pid;

// 	printf("entrou no execute\n");
// 	status = 0x7F;
// 	pipeline_matrix(ms);
// 	last_child_pid = pipeline_exec(ms->cmd_list, ms);     ANTERIOR ANTERIOR ANTERIOR
// 	if (last_child_pid > 0)
// 	{
// 		last_child_pid = waitpid(last_child_pid, &status, 0);
// 		while (waitpid(0, NULL, 0) > 0)
// 			continue ;
// 		if (WIFEXITED(status))
// 			set_exit_status(WEXITSTATUS(status));
// 		printf("Pipeline concluído com status: %d\n", WEXITSTATUS(status));
// 	}
// 	set_signals();
// }

void execute(t_minish *ms)
{
    int status;
    pid_t pid;

    pipeline_matrix(ms);
    pid_t last_child_pid = pipeline_exec(ms->cmd_list, ms);

    // Esperar por todos os processos filhos
    while ((pid = waitpid(-1, &status, 0)) > 0)
    {
        if (pid == last_child_pid)
        {
            if (WIFEXITED(status))
                set_exit_status(WEXITSTATUS(status));
            else if (WIFSIGNALED(status))
                set_exit_status(128 + WTERMSIG(status));
        }
    }
    set_signals();
}

// void execute(t_minish *ms)
// {
//     int status;
//     pid_t last_child_pid;
//     pid_t pid;

//     pipeline_matrix(ms);
//     //printf("Executando pipeline...\n");

//     last_child_pid = pipeline_exec(ms->cmd_list, ms);

//     // Espera por todos os processos filhos
//     while ((pid = waitpid(-1, &status, 0)) > 0)
//     {
//         if (pid == last_child_pid)
//         {
//             // Se for o último processo, salva o status de saída
//             if (WIFEXITED(status))
//                 set_exit_status(WEXITSTATUS(status));
//             else if (WIFSIGNALED(status))
//                 set_exit_status(128 + WTERMSIG(status));
//         }
//     }

//     printf("Pipeline concluído com status: %d\n", get_exit_status());
//     set_signals();
// }
