/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/10/16 16:01:15 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*void	pipeline_create(void)
{
	int	i;

	(ms()->pipes) = ft_calloc(ms()->num_commands, sizeof(int *));
	if (!ms()->pipes)
		return ;
	i = -1;
	while (++i < ms()->num_commands - 1)
	{
		(ms()->pipes[i]) = ft_calloc(2, sizeof(int));
		pipe(ms()->pipes[i]);
	}
}*/

// 	-> Gera uma nova matriz de pipes. A matriz é uma matriz 2D de inteiros, onde cada linha representa um pipe.
//	-> A primeira coluna é o descritor do ficheiro de entrada e a segunda coluna o descritor do ficheiro de saída;

void	pipeline_matrix(t_minish *ms)
{
	int	i;

	i = 0;
	ms->pipes = ft_calloc(ms->cmd_num, sizeof(int *)); // colocar um list_size dos cmds -1;
	//															aloca a qunatidade de linhas da matrix;
	//															cada linha corresponde a um pipe;
	if (!ms->pipes)
		return ;
	while (i < ms->cmd_num - 1) // aloca as duas colunas da matrix, entrada e saida do pipe.
	{
		ms->pipes[i] = ft_calloc(2, sizeof(int));
		if (!ms->pipes[i])
			return ;
		pipe(ms->pipes[i]);
		i++;
	}
}

/*
void	pipeline_apply(int command_index)
{
	if (ms()->num_commands < 2)
		return ;
	if (ms()->in_fd == STDIN_FILENO)
		if (command_index != 0)
			ms()->in_fd = ms()->pipes[command_index - 1][READ_END];
	if (ms()->out_fd == STDOUT_FILENO)
		if (!is_last_command(command_index))
			ms()->out_fd = ms()->pipes[command_index][WRITE_END];
}

bool	is_last_command(int command_index)
{
	return (command_index == ms()->num_commands - 1);
}

bool	need2be_root(char *command, char *arg)
{
	return (!ft_strcmp(command, "cd") || !ft_strcmp(command, "exit") \
		|| (!ft_strcmp(command, "export") && arg) || !ft_strcmp(command, "unset") \
		|| !ft_strcmp(command, "ptmp"));
}

bool	is_builtin(char *command)
{
	return (!ft_strcmp(command, "exit") || !ft_strcmp(command, "pwd") \
		|| !ft_strcmp(command, "env") || !ft_strcmp(command, "echo") \
		|| !ft_strcmp(command, "unset") || !ft_strcmp(command, "export") \
		|| !ft_strcmp(command, "cd") || !ft_strcmp(command, "ptmp"));
}

void	_execute_if_exists(char *exe, char **argv)
{
	char		*path;
	struct stat	path_stat;

	path = get_executable_path(exe);
	stat(path, &path_stat);
	if (path)
	{
		if (S_ISDIR(path_stat.st_mode))
			error(ANSI_RED, ERROR_DIRECTORY, path, 126);
		else if (S_ISREG(path_stat.st_mode))
		{
			execve(path, argv, ms()->envp);
			error(ANSI_RED, ERROR_NO_PERMISSIONS, exe, 126);
		}
		ft_free(path);
	}
	else
		error(ANSI_RED, ERROR_UNKNOWN_CMD, exe, 127);
	return ;
}

void	_execute_command(char **args)
{
	(ms()->exit_status) = 0;
	if (!is_builtin(args[0]))
		_execute_if_exists(args[0], args);
	else if (!ft_strcmp(args[0], "exit"))
		ft_exit(args + 1);
	else if (!ft_strcmp(args[0], "pwd"))
		printf("%s\n", ms()->cwd);
	else if (!ft_strcmp(args[0], "env"))
		ft_env(args + 1);
	else if (!ft_strcmp(args[0], "echo"))
		ft_echo(args + 1);
	else if (!ft_strcmp(args[0], "unset"))
		ft_unset(args + 1);
	else if (!ft_strcmp(args[0], "export"))
		ft_export(args + 1);
	else if (!ft_strcmp(args[0], "cd"))
		ft_cd(args + 1);
	else if (!ft_strcmp(args[0], "ptmp"))
		tmp_debug();
}

pid_t	_execute_forkable(t_ast *command)
{
	pid_t	pid;

	signals_child();
	pid = fork();
	if (pid == 0)
	{
		if (ms()->in_fd == -1 || ms()->out_fd == -1)
			sanitize(true);
		pipeline_apply(command->index);
		io_connect();
		_execute_command(command->args);
		sanitize(true);
	}
	io_disconnect(command->index);
	return (pid);
}

pid_t	_execute_pipeline(t_ast *node)
{
	pid_t	last;

	last = 0;
	if (!node)
		return (last);
	last = _execute_pipeline(node->left);
	last = _execute_pipeline(node->right);
	if (!is_redir_or_pipe(node->token))
	{
		if (is_is_root(node->args[0], node->args[1]))
			_execute_command(node->args);
		else
			last = _execute_forkable(node);
	}
	else if (is_redirection(node->token))
		execute_redirection(node->token->type, node->args[0]);
	return (last);
}*/

bool	need2be_parent(char *command, char *arg)
{
	bool	is_parent;

	is_parent = false;
	if (ft_str_cmp(command, "cd") == true)
		is_parent = true;
	else if (ft_str_cmp(command, "exit") == true)
		is_parent = true;
	else if (ft_str_cmp(command, "export") == true && arg != NULL)
		is_parent = true;
	else if (ft_str_cmp(command, "unset") == true)
		is_parent = true;

	return (is_parent);
}

bool	is_valid(char *word)
{
	int	j;

	j = 1;
	while (word[j])
	{
		if (word[j] != 'n')
			return (false);
		j++;
	}
	return (true);
}

void	echo(char	**words)
{
	int		i;
	bool	only_n;

	i = 0;
	only_n = true;
	while (words[i] && words[i][0] == '-')
	{
		if (!is_valid(words[i]))
			break ;
		only_n = true;
	}
	while (words[i])
	{
		printf("%s", words[i]);
		i++;
		if (words[i])
			printf(" ");
	}
	if (only_n)
		printf("\n");
}

void	error(char *str, int status)
{
	printf("%s", str);
	set_exit_status(status);
}

char	*skip_whitespace(char *str)
{
	while ((*str >= 9 && *str <= 13) || (*str == ' '))
		str++;
	return (str);
}

long long	ft_atoll(char *str)
{
	unsigned long long	num;
	int					sign;

	num = 0;
	sign = 1;
	str = skip_whitespace(str);// nao usei a do atoi por ser static
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (*str < '0' || *str > '9')
		return (255);
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str++ - '0');
		if ((sign > 0 && num > (unsigned long long)LLONG_MAX) || \
			(sign < 0 && num > (unsigned long long)-(LLONG_MIN)))
			return (255);
	}
	if (*str)
		return (255);
	return ((long long)(num * sign));
}

long long	validate_and_convert_arg(char *arg)
{
	long long	num;

	num = ft_atoll(arg);
	if (num == 255)
	{
		error("exit: numeric argument required\n", 255);
		sanitize(true);
	}
	return (num);
}

long long	calculate_exit_code(long long num)
{
	num = num % 256;
	if (num < 0)
		num += 256;
	return (num);
}

void	exit_bash(char **exit_args)
{
	size_t		arg_num;
	long long	num;

	arg_num = 0;
	num = 0;
	while (exit_args[arg_num])
		arg_num++;
	if (arg_num > 1)
	{
		error("exit: too many arguments\n", 1);
		return ;
	}
	if (arg_num == 1)
	{
		num = validate_and_convert_arg(exit_args[0]);
		num = calculate_exit_code(num);
		set_exit_status(num);
	}
	sanitize(true);
}

void	env(char **env_arg, char **env_list)
{
	int	i;

	i = 0;
	if (env_arg[1] != NULL)
	{
		error("env: no such file or directory: \n", 127);
		return ;
	}
	while (env_list[i])
	{
		printf("%s\n", env_list[i]);
		i++;
	}
}

void print_export(t_minish *ms)
{
	int		i;
	char	*equals_sign;

	i = 0;
	while (ms->env_list[i])
	{
		equals_sign = ft_strchr(ms->env_list[i], '=');
		if (equals_sign)
			printf("declare -x %s\n", ms->env_list[i]);
		else
			printf("declare -x %s=\"\"\n", ms->env_list[i]);  // Variável sem valor
		i++;
	}
}

void	add_new_env(char ***target_env, const char *assignment)
{
	int		i;
	char	**new_env_list;
	int		j;

	i = 0;
	j = 0;
	while ((*target_env)[i])
		i++;
	new_env_list = malloc(sizeof(char *) * (i + 2));
	if (!new_env_list)
		return ;
	while (j < i)
	{
		new_env_list[j] = target_env[j];
		j++;
	}
	new_env_list[i] = ft_strdup(assignment);
	new_env_list[i + 1] = NULL;
	free(*target_env);
	*target_env = new_env_list;
}

int	ft_strlen_sep(const char *s, char *seps)
{
	int	i;

	i = 0;
	while (s[i] && !ft_strchr(seps, s[i]))
		i++;
	return (i);
}

int	find_env_index(char **target_env, const char *assigment)
{
	int		i;
	size_t	len;
	char	*key;

	key = ft_substr(assigment, 0, ft_strlen_sep(assigment, '='));
	len = ft_strlen(key);
	i = 0;
	while (target_env[i])
	{
		// Verifica se o nome da variável corresponde até o '='
		if (ft_strncmp(target_env[i], key, len) == 0 && \
		target_env[i][len] == '=')
		{
			free(key);
			return (i);
		}
		i++;
	}
	free(key);
	return (-1);//se não for encontrada
}

void	add_or_update_env(char ***target_env, const char *assignment)
{
	int		index;

	index = find_env_index(*target_env, assignment);
	if (index != -1)
	{
		free((*target_env)[index]);
		(*target_env)[index] = ft_strdup(assignment);
	}
	else
		add_new_env(target_env, assignment);
}

void	handle_no_assignment(t_minish *ms, char *arg)
{
	char	*empty_assign;

	if (find_env_in_tmp(ms, arg))
		add_or_update_env(ms->env_tmp, arg);
	else
	{
		// Cria a string "key="
		empty_assign = malloc(ft_strlen(arg) + 2);
		if (!empty_assign)
			return ;
		//copiar o conteúdo de arg para empty_assign
		ft_strlcpy(empty_assign, arg, ft_strlen(arg) + 1);
		//concatenar "=" no final de empty_assign
		ft_strlcat(empty_assign, "=", ft_strlen(arg) + 2);
		// Adiciona ao env_list
		add_or_update_env(&ms->env_list, empty_assign);
		free(empty_assign);
	}
}

int	find_env_in_tmp(t_minish *ms, const char *name)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	while (ms->env_tmp[i])
	{
		// Verifica se a var em env_tmp começa com name seguido por '='
		if (!ft_strncmp(ms->env_tmp[i], name, len) && \
		ms->env_tmp[i][len] == '=')
			return (1);  // encontrada em env_tmp
		i++;
	}
    return (0);  // não encontrada em env_tmp
}

char	*extract_key(const char *assignment)
{
	size_t	len;
	char	*key;

	len = ft_strlen_sep(assignment, '=');
	key = ft_substr(assignment, 0, len);
	return (key);
}

void	copy_env_except_key(char **src, char **dest, const char *key, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (!(ft_strncmp(src[i], key, len) == 0 && src[i][len] == '='))
		{
			dest[j] = src[i];
			j++;
		}
		else
		{
			free(src[i]);
		}
		i++;
	}
	dest[j] = NULL;
}

void	remove_from_tmp(t_minish *ms, const char *key)
{
	int		i;
	int		len;
	char	**new_env_tmp;

	len = ft_strlen(key);
	i = 0;
	while (ms->env_tmp[i])
		i++;
	new_env_tmp = malloc(sizeof(char *) * i);
	if (!new_env_tmp)
		return ;
	copy_env_except_key(ms->env_tmp, new_env_tmp, key, len);
	free(ms->env_tmp);
	ms->env_tmp = new_env_tmp;
}

void	handle_assignment(t_minish *ms, char *arg)
{
	char	*key;

	key = extract_key(arg);
	// Verificar se está em env_tmp antes de adicionar diretamente a env_list
	if (find_env_in_tmp(ms, key))
		remove_from_tmp(ms, key);
	free(key);
	add_or_update_env(&ms->env_list, arg);
}

void	export(char **exp_args, t_minish *ms)
{
	int	i;

	i = 0;
	if (!exp_args[0])
		print_export(ms);
	while (exp_args[i])
	{
		if (ft_strchr(exp_args[i], '='))
			handle_assigment(ms, exp_args[i]);
		else
			handle_no_assigment(ms, exp_args[i]);
		i++;
	}
}

void	do_command(char	**cmd, t_minish *ms)
{
	set_exit_status(0);
	//fazer uma verificacacao se eh builtin ou eh caminho. WIP
	if (ft_str_cmp(cmd[0], "pwd"))
		printf("%s\n", ms->cwd);
	if (ft_str_cmp(cmd[0], "echo"))
		echo(cmd + 1);
	if (ft_str_cmp(cmd[0], "exit"))
		exit_bash(cmd + 1);
	if (ft_str_cmp(cmd[0], "env"))
		env(cmd + 1, ms->env_list);
	if (ft_str_cmp(cmd[0], "export"))
		export(cmd + 1, *ms);
}

void	handle_child_quit(int signal)
{
	if (signal != SIGQUIT)
		return ;
	ft_putstr_fd("quit: 3\n", 2); // escreve como erro;
	set_exit_status(130);// 128 mais numero do sinal
}

void	handle_child_interrupt(int signal)
{
	if (signal != SIGINT)
		return ;
	ft_putstr_fd("\n", 2); // escreve como erro;
	set_exit_status(131);// 128 + numero do sinal
}

void	treat_child_signal(void)
{
	signal(SIGQUIT, handle_child_quit); //lida com o uso de ctrl + \ durante um processo child, testar sleep 10 e ctrl '\'
	signal(SIGINT, handle_child_interrupt);
}

void	pipe_data_flow(int cmd_index, t_minish *ms)
{
	if (ms->cmd_num <= 1)
		return ;
	if (ms->fd_in == 0)
		if (cmd_index > 0)
			ms->fd_in = ms->pipes[cmd_index - 1][0];
	if (ms->fd_out == 1)
		if(cmd_index != ms->cmd_num - 1)
			ms->fd_out = ms->pipes[cmd_index][1];
}

void	relinking_in_out(t_minish *ms)
{
	if (ms->fd_in >= 0)
		dup2(ms->fd_in, 0);
	if (ms->fd_in >= 1)
		dup2(ms->fd_out, 1);
}

pid_t	child_exec(t_ast *cmd, t_minish *ms)
{
	pid_t	pid;
	
	treat_child_signal();
	pid = fork();
	if (pid == 0) // estamos na child
	{
		pipe_data_flow(cmd->index, ms);
		relinking_in_out(ms);
		do_command(cmd->cmd, ms);
		//sanitize;
	}
}

pid_t	pipeline_exec(t_ast	*node, t_minish *ms)
{
	pid_t	last_child_pid;

	last_child_pid = 0;
	if (!node)
		return (last_child_pid);
	last_child_pid = pipeline_exec(node->left); // verifica ate a ultima leaf a esquerda.
	last_child_pid = pipeline_exec(node->right); // verifica ate a ultima leaf da direita.
	if (!is_redir_or_pipe(node->token)) // verifica se o token atual nao eh um pipe ou redirect.
	{
		if (need2be_parent(node->cmd[0], node->cmd[1])) // envia o nome do comando e no caso export tbm verifica se é o export de alterar variaveis
			do_command(node->cmd, ms);
		else
			last_child_pid = child_exec(node, ms);
	}
	return (last_child_pid);
}

void	execute(t_minish *ms, t_ast	*ast)
{
/*	int		status;
	pid_t	last;

	status = 0x7F;
	pipeline_create();
	last = _execute_pipeline(ast);
	last = waitpid(last, &status, 0);
	while (waitpid(0, NULL, 0) > 0)
		continue ;
	if (WIFEXITED(status))
		ms()->exit_status = WEXITSTATUS(status);
	signals();*/

	int		status;
	pid_t	last_child_pid;

	status = 0x7F; // = 127 -> numero usado para erro antes de executar os processos = erro ao exec comando
	pipeline_matrix(ms);
	last_child_pid = pipeline_exec(ast, ms);
	
	//feito - criar um int** onde regista comandos, de alguma forma
	//WIP executar pipeline, gravar pid (criado com fork()?) respectivo em "child_pid"
	//WIP child_pid = waitpid(child_pid, &status, 0);
	//WIP esperar até terminarem todos os child processes antes de continuar o programa
	//WIP se o processo terminar normalmente, gravar o seu exit_status
	//WIP ?signals()?
}
