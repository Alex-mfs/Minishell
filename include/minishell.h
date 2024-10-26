/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:45:30 by alfreire          #+#    #+#             */
/*   Updated: 2024/10/26 11:07:20 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <time.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
//# include <sys/types.h>
//# include <sys/wait.h>
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
	struct s_token	*next;
}			t_token;

typedef struct s_ast
{
	int				index;
	char			*cmd;
	char			**args;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_ast	*next;
}			t_ast;

typedef struct s_minish
{
	int				**pipes;
	char			**path;
	char			**env_list;
	char			**env_tmp;
	char			*cwd;
	struct s_token	*tk_list;
	struct s_ast	*cmd_list;
	int				fd_in;
	int				fd_out;
}			t_minish;

//Utils - Initialising
void	init_ms(t_minish *ms, char **envp);
//Utils - Signaling
void	set_signals(void);
void	set_signals_heredoc(void);
void	treat_child_signal(void);

//Utils - Handling
void	handle_interrupt(int signum);
void	handle_child_interrupt(int signal);
void	handle_child_quit(int signal);
void	handle_heredoc_interrupt(int signum);

//Utils - Validating
bool	validate_quotes(char *input);
bool	validate_tokens(t_minish *ms);
//Utils - Reading
void	read_inputs(t_minish *ms);
//Utils - Tokening
void	get_tokens(t_minish *ms, char *input);
//Utils - Expanding
void	expand(t_minish *ms);
//Utils - Parsing
void	parse(t_minish *ms);
//Utils - Executing
void	execute(t_minish *ms);
//Utils - Sanitizing
void	sanitize_ms(t_minish *ms, bool sair);
void	sanitize_envp(t_minish *ms);

//executing_aux
void	error(char *str, int status);
bool	is_redir_or_pipe(char *cmd);
bool	is_redirection(char *cmd);
bool	need2be_parent(char *command, char *arg);

//pipeline
void	pipeline_matrix(t_minish *ms);
void	close_in_out(int index, t_minish *ms);
void	relinking_in_out(t_minish *ms);
//void	pipe_data_flow(int cmd_index, t_minish *ms);
void	pipe_data_flow(int cmd_index, t_minish *ms, char **fullcmd);
void	exec_if_exists(char **arg, t_minish *ms);

//minishell.c - exit_status
void	set_exit_status(int status);
int		get_exit_status(void);


//commands
void	exit_bash(char **exit_args, t_minish *ms);
void	ft_export(char **exp_args, t_minish *ms);
void	env(char **env_arg, char **env_list);
char	*get_env(const char *key, char **env_list);
void	echo(char **words);
void	unset(char **vars, t_minish *ms);
void	cd(char **tokens, t_minish *ms);

//export_aux
int		ft_strlen_sep(const char *s, char *seps);
char	*extract_key(const char *assignment);
void	copy_env_except_key(char **src, char **dest, const char *key, int len);
void	remove_from_tmp(t_minish *ms, const char *key);
int		find_env_in_tmp(t_minish *ms, const char *name);
int		find_env_index(char **target_env, const char *assigment);
void	add_new_env(char ***target_env, const char *assignment);
void	add_or_update_env(char ***target_env, const char *assignment);

//path
char	*get_executable_path(char *cmd, t_minish *ms);

//Redirection
void	execute_redir(const char *type, char *filename, t_minish *ms);

//Utils(?) - cmd_listing
int		cmdlst_size(t_ast *lst, bool total);
t_ast	*cmdlst_last(t_ast *lst);
void	cmdlst_addback(t_ast **lst, t_ast *new);
int		lastpipe_index(t_ast *lst);
//Utils(?) - tk_listing
void	tklst_addback(t_token **lst, t_token *new);

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