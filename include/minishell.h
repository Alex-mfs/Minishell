/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:45:30 by alfreire          #+#    #+#             */
/*   Updated: 2024/12/02 09:05:57 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <time.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"

typedef enum e_lexer
{
	REDIR_INPUT_1,
	REDIR_OUTPUT_1,
	REDIR_INPUT_2,
	REDIR_OUTPUT_2,
	PIPE,
	SINGLE_QUOTES,
	DOUBLE_QUOTES,
	OTHER,
}	t_lexer;

typedef struct s_token
{
	char			*token;
	t_lexer			type;
	bool			to_merge;
	bool			empty_quotes;
	struct s_token	*next;
}			t_token;

typedef struct s_ast
{
	int				index;
	char			*cmd;
	char			**args;
	bool			empty_quotes;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_ast	*next;
	struct s_ast	*redirections;
}			t_ast;

typedef struct s_minish
{
	int				**pipes;
	char			**path;
	char			**env_list;
	char			**env_tmp;
	char			*cwd;
	struct s_token	*tk_list;
	bool			aux_merge;
	bool			empty_command;
	bool			good_assign;
	t_ast			*current_node;
	struct s_ast	*cmd_list;
	int				fd_in;
	int				fd_out;
	int				qtd_pipes;
	bool			dont_execve;
	int				hd;
}			t_minish;

//Utils - Initialising
void	init_ms(t_minish *ms, char **envp);
void	set_exit_status(int status);
int		get_exit_status(void);
//Utils - Reading
void	read_inputs(t_minish *ms);
//Utils - Validating
bool	validate_quotes(char *input);
bool	validate_tokens(t_minish *ms, bool merged);
//Utils - Signaling
void	set_signals(void);
// void	set_signals_heredoc(void);
void	treat_child_signal(void);
void	sig_ignore(void);
//Utils - Handling
void	handle_interrupt(int signum);
void	handle_child_interrupt(int signal);
void	handle_child_quit(int signal);
void	handle_hd_int(int signum, t_minish *ms, char *delimiter, char *hd);
//Utils - Sanitizing
void	sanitize_ms(t_minish *ms, bool sair);
void	sanitize_path(t_minish *ms);
void	cmd_clear(t_ast **lst);
void	tk_clear(t_token **lst);
void	unlink_hd_file(t_minish *ms);

//Parse
void	get_tokens(t_minish *ms, char *input);
void	expand(t_minish *ms);
void	parse(t_minish *ms);
void	empty_cmd(t_minish *ms, t_ast *node);
//Parse - Listing
int		cmdlst_size(t_ast *lst, bool total);
t_ast	*cmdlst_penult(t_ast *lst);
t_ast	*cmdlst_last(t_ast *lst);
void	cmdlst_addback(t_ast **lst, t_ast *new);
t_ast	*lastpipe(t_ast *lst);
void	tklst_addback(t_token **lst, t_token *new);
t_token	*clear_top_token(t_token *node);
bool	token_assign(t_token *buff);
void	merge_tokens(t_minish *ms);
//Parse - Checking
bool	is_tk_redpip(t_token *tk);
bool	is_tk_miniredir(t_token *tk);
bool	is_tk_quote(t_token	*tk);
bool	is_tk_merge(t_token	*tk);

//Execution - Executing
void	execute(t_minish *ms);
//Execution - Executing_aux
void	error(char *str, int status);
void	error_execve(t_minish *ms);
char	*which_error(char *bef, char *mid, char *aft);
bool	is_redir_or_pipe(char *cmd);
bool	is_redirection(char *cmd);
bool	process_redirections(t_ast *node, t_minish *ms);
void	deal_with_isdir(t_minish *ms, char **arg, char *path);
bool	need2be_parent(char *command, char *arg, t_minish *ms);
bool	is_builtin(char *command);
char	**join_cmd_arg(char	*cmd, char **args);
//Execution - Pipeline
void	pipeline_matrix(t_minish *ms);
void	close_in_out(int index, t_minish *ms);
void	relinking_in_out(t_minish *ms);
void	pipe_data_flow(int cmd_index, t_minish *ms);
void	exec_if_exists(char **arg, t_minish *ms, t_ast *node);
//Execution - Path
char	*get_executable_path(char *cmd, t_minish *ms);
//Execution - Redirection + aux
bool	execute_redir(const char *type, char *filename, t_minish *ms);
void	read_until_deli(char *deli, t_minish *ms, char *file, bool fl);
char	*create_hd_file(t_minish *ms, bool flag, int i);
void	hd_sanitize(t_minish *ms, int e_code);
int		do_heredoc(char *delimiter, t_minish *ms);

//Commands
void	exit_bash(char **exit_args, t_minish *ms, int tmp);
void	ft_export(char **exp_args, t_minish *ms);
void	env(char **env_arg, char **env_list);
char	*get_env(const char *key, char **env_list);
void	echo(char **words);
void	unset(char **vars, t_minish *ms);
void	cd(char **tokens, t_minish *ms);
//Commands - Export_aux
int		ft_strlen_sep(const char *s, char *seps);
char	*extract_key(const char *assignment);
void	copy_env_except_key(char **src, char **dest, const char *key, int len);
void	remove_from_tmp(t_minish *ms, const char *key);
int		find_env_in_tmp(t_minish *ms, const char *name);
int		find_env_index(char **target_env, const char *assigment);
void	add_new_env(char ***target_env, const char *assignment);
void	add_or_update_env(char ***target_env, const char *assignment);

#endif

/*# define ANSI_BLACK		"\033[30m"
# define ANSI_RED		"\033[31m"
# define ANSI_GREEN		"\033[32m"
# define ANSI_YELLOW	"\033[33m"
# define ANSI_BLUE		"\033[34m"
# define ANSI_MAGENTA	"\033[35m"
# define ANSI_CYAN		"\033[36m"
# define ANSI_GRAY		"\033[37m"
# define ANSI_LRED		"\033[91m"
# define ANSI_LGREEN	"\033[92m"
# define ANSI_LYELLOW	"\033[93m"
# define ANSI_LBLUE		"\033[94m"
# define ANSI_LMAGENTA	"\033[95m"
# define ANSI_LCYAN		"\033[96m"
# define ANSI_WHITE		"\033[97m"
# define ANSI_RST		"\033[0m"
# define ANSI_BOLD		"\033[1m"
# define ANSI_UNDERLINE	"\033[4m"*/

//valgrind
// --leak-check=full --show-leak-kinds=all --suppressions=suppression_file
// ./minishell
//
/*{
   name
   Memcheck:Leak
   fun:*alloc
   ...
   obj:*//*libreadline.so.*
   ...
}
{
    leak readline
    Memcheck:Leak
    ...
    fun:readline
}
{
    leak add_history
    Memcheck:Leak
    ...
    fun:add_history
}*/