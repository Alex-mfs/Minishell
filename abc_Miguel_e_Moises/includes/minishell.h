/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:45:27 by madao-da          #+#    #+#             */
/*   Updated: 2024/11/30 18:45:33 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <linux/limits.h>  // For PATH_MAX
# include <fcntl.h>  // For open function
# include <unistd.h>  // For write and read functions
# include <stdio.h>  // For printf
# include <stdlib.h>  // For malloc, free, exit
# include <string.h>  // For strerror
# include <errno.h>  // For errno
# include <sys/types.h>  // For pid_t
# include <sys/wait.h>  // For waitpid
# include <sys/stat.h>  // For stat
# include <sys/ioctl.h>
# include <signal.h>  // For signal
# include <stdbool.h>  // For bool
# include <dirent.h>  // For opendir
# include <readline/readline.h>  // For readline
# include <readline/history.h>  // For add_history
# include "../LIBFT/src/libft.h"
# include <limits.h>
# include <termios.h>

extern int	g_sig_num;

// ENVIRONMENT
# define MAX_ENV		1024 // Can be changed to 4096

// SIGNALS
# ifndef ECHOCTL
#  define ECHOCTL 0000400
# endif

// GENERAL COMMAND STRUCT
typedef struct s_cmd
{
	int	type;
}		t_cmd;

// EXECUTION NODE STRUCT
typedef struct s_exec
{
	int		type;
	char	**argv;
}			t_exec;

// REDIRECTION NODE STRUCT
typedef struct s_redir
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	int		mode;
	int		fd;
}			t_redir;

// PIPE NODE STRUCT
typedef struct s_pipe
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}			t_pipe;

// FILE DETAILS STRUCT
typedef struct s_file
{
	char	*file;
	int		mode;
	int		fd;
}			t_file;

// MINISHELL MAIN DATA STRUCT
typedef struct s_data
{
	char	*prompt;
	char	*input;
	t_cmd	*tree;
	t_list	*lst_nodes;
	int		return_code;
	int		heredoc_count;
	char	**variables;
	char	*filename;
	bool	no_string;
}			t_data;

// SIGNALS
# define NO_SIG			0
# define S_SIGQUIT		1
# define S_SIGINT		2
# define S_SIGEOF		3

// PARSED NODE TYPES
# define EXEC			1
# define REDI			2
# define PIPE			3

// PARSING DICTIONARIES
# define MS_SPACE		" \t\r\n\v"
# define MS_TOKENS		"<|>"
# define MS_QUOTES		"\"\'"
# define MS_VAR_CHAR	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\
0123456789_"

// TOKEN SYMBOLS
# define TOKEN_PIPE		'|'
# define TOKEN_INPU		'<'
# define TOKEN_OUTP		'>'
# define TOKEN_DELI		'd'
# define TOKEN_APPE		'a'
# define TOKEN_TEXT		't'
# define TOKEN_EOF		'\0'
# define TOKEN_ERROR	-1

// HEREDOC FILE LIMIT
# define HEREDOC_LIMIT	999

// RETURN CODES
# define GENERAL_ERROR	1
# define SHELL_BUILT_IN	2
# define CMD_NOT_EXEC	126
# define SIG_INT_TERM	130

// HEREDOC
# define HEREDOC_FOLDER	"/tmp/"
# define HEREDOC_NAME	"heredoc_"
# define HEREDOC_FILE	"/tmp/heredoc_"
# define HEREDOC_EXTEN	".tmp"

// ERROR CODES
# define NO_ERROR		0
# define MALLOC			1
# define SYNTAX			2
# define QUOTE			3
# define ARG_LIMIT		4
# define HEREDOC		5
# define HEREDOC_CTRL_D	6
# define FORK			7
# define REDIR_FILE		8

// ERROR MESSAGES
# define MSG_MINISHELL	"minishell: "
# define MSG_MALLOC		"malloc: Cannot allocate memory"
# define MSG_FORK		"fork: Cannot allocate memory"
# define MSG_SYNTAX		"syntax error near unexpected token "
# define MSG_QUOTE		"unexpected EOF while looking for matching "
# define MSG_ARG_LIMIT	": Argument list too long"
# define MSG_HEREDOC	"cannot create heredoc file (limit reached)"
# define MSG_HDOC_CTRLD "warning: here-document delimited by end-of-file \
(wanted `"
# define MSG_REDIR_FILE	": ambiguous redirect"

void	handle_heredoc(int sig, t_data *ms_data, char *delimiter, int fd);

// INITIALIZE / CLOSE / FREE
t_data	*init_minishell(char **envp, int return_code);
char	*free_str(char *str);
t_cmd	*free_tree(t_cmd *node);
void	free_exec(t_cmd *node);
void	ft_del(void *content);
void	lst_clean(t_list **lst);
void	delete_variables(char **variables);
void	free_environment(char **envp);
void	clean_shell(t_data *ms_data);

// PARSER - CREATE ABSTRACT SYNTAX TREE
t_cmd	*exec_node(void);
t_cmd	*redir_node(t_cmd *sub_node, t_file *file);
t_cmd	*pipe_node(t_cmd *left, t_cmd *right);
char	*expand_var(t_data *ms_data, char *start, char *end, char **str);
char	*substr(char *start, char *end);
char	*concat_str(char *str, char *sub_start, char *sub_end);
char	*substr_expans(t_data *ms_data, char *start, char *end);
int		look_token(char **input, char *tokens);
char	*parse_text(t_data *ms_data, char *str, int *token);
int		parse_token(t_data *ms_data, char **input, char **stoken, \
char **etoken);
int		fill_argv(t_data *ms_data, char *stoken, t_exec *exec);
int		exit_heredoc(t_data *ms_data, char *delimiter, int fd, int r_code);
int		write_heredoc(t_data *ms_data, char *delimiter, int fd);
t_cmd	*heredoc_node(t_data *ms_data, t_cmd *node, char *delimiter);
t_cmd	*seq_redir(t_data *ms_data, t_cmd *node, t_file *file);
t_cmd	*parse_redir(t_data *ms_data, t_cmd *node, char **input);
t_cmd	*parse_pipe(t_data *ms_data, char **input);
t_cmd	*create_tree(t_data *ms_data);
t_cmd	*check_node(t_data *ms_data, t_cmd *node);
char	*check_str(t_data *ms_data, char *str);
char	**check_str_2d(t_data *ms_data, char **str);
int		check_fd(t_data *ms_data, int fd);
char	*check_readline(t_data *ms_data, char *str, char *delimiter);
int		check_argv(t_data *ms_data, char **argv, int argc);
t_file	*check_file(t_data *ms_data, t_file *file);
pid_t	check_fork(t_data *ms_data, pid_t pid);
char	*check_red(t_data *ms_data, char *stoken, char *str);

// EXECUTION
void	exec_tree(t_cmd *tree, t_data *ms_data);
char	*find_executable(char *command, t_data *ms_data);
void	handle_redirection(t_redir *redir_cmd); // NOT IN USE
void	ft_exec_builtin(char **argv, t_data *ms_data);
void	print_test(void);

// BUILT-IN FUNCTIONS
bool	search_builtin(char *command);
void	ft_exec_builtin_2(char **argv, t_data *ms_data, char *pwd);
void	handle_cd(t_data *ms_data, char **argv, char *pwd);
int		handle_absolut_path(char *line, t_data *ms_data);
int		handle_home(t_data *ms_data);
int		ft_is_char(char c);
int		handle_dot_cases(char *line, t_data *ms_data);
int		handle_relative_path(char *line, t_data *ms_data);
void	handle_echo(char **argv);
int		str_is_simple(char *str);
void	handle_env(char **argv, t_data *ms_data);
void	handle_exit(char **argv, t_data *ms_data, char *pwd);
void	handle_export(char **argv, t_data *ms_data);
void	export_helper(char *name, t_data *ms_data, int i);
void	export_env(t_data *ms_data);
void	handle_pwd(char **argv, t_data *ms_data);
void	handle_unset(char **argv, t_data *ms_data);

// ENVIROMENT
char	**copy_environment(char **envp);
char	**expand_environment(char **envp, char *var, t_data *ms_data);
void	add_variable(char **envp, const char *var);
char	**reduce_environment(char **envp, char *var, t_data *ms_data);
void	remove_variable(char **envp, const char *var);
char	*my_getenv_expans(char *var_name, char **variables);
char	*my_getenv(char *var_name, char **variables);
int		find_variable(char **envp, const char *name);
char	*ft_strndup(const char *s1, size_t n);
int		is_variable_name_ok(char *name);

// ERROR HANDLING
void	set_return_code(t_data *ms_data, int error_code);
void	print_error(t_data *ms_data, int error_code, char *error_info);
void	print_syntax_error(t_data *ms_data, int token);
void	print_exec_error(char *error_message, char *command);
void	print_error_msg_quotes(char *msg, char *info);
void	handle_path_errors(char *path, t_data *ms_data);
void	prepare_error(char *error_message, char *command, t_data *ms_data, \
int return_code);

// SIGNALS
/* void	handle_signals(t_data *ms_data);
void	handle_sigint(int sig); */
void	handle_signals(t_data *ms_data);
void	handle_sigint(int sig, siginfo_t *info, void *context);
void	handle_eof(int sig);
void	update_pwd(char *pwd, t_data *ms_data);
char	*ft_strsep(char **str, const char *delim);
size_t	ft_strcspn(const char *s1r, const char *s2r);
int		ft_strcmp(char *s1, char *s2);
void	prepare_cd_error(char *error_message, char *command, t_data *ms_data, \
int error_code);
int		relative_path_helper(char *path, t_data *ms_data, char *line);
int		prepare_exit_error(char *error_message, char *arg, \
t_data *ms_data, int exit_code);
int		check_arg2(char **argv, t_data *ms_data);
void	delete_remaining_variables(char **variables, int len);
int		initial_checks_expander(char **envp, char *var, t_data *ms_data);
int		expander_helper(char **envp, char **new_envp, char *var, \
t_data *ms_data);
int		delete_remain_reducer(char **variables, int len, \
t_data *ms_data);
int		reducer_helper(char **envp, char **new_envp, \
t_data *ms_data, int index);
char	*get_original_path(void);
char	*get_original_path(void);
int		cleaner_original_path(char *original_path, char *full_path);
void	update_old_pwd(char *old_pwd, char *old_pwd_str, t_data *ms_data);
void	update_new_pwd(char *new_pwd, char *new_pwd_str, t_data *ms_data);
void	prepare_to_exit(t_data *ms_data, char *pwd, int exit_code);
void	case_pipe(t_pipe *pipe_cmd, t_data *ms_data);
void	case_redir(t_cmd *tree, t_data *ms_data);
void	case_exec(t_exec *exec_cmd, t_data *ms_data);
char	*get_executable_path(t_exec *exec_cmd, t_data *ms_data);
void	handle_executable(char *executable, t_exec *exec_cmd, t_data *ms_data);
void	setup_pipe_exec_left(t_pipe *pipe_cmd, t_data *ms_data, int *pipe_fd, \
pid_t pid);
void	setup_pipe_exec_right(t_pipe *pipe_cmd, t_data *ms_data, int *pipe_fd, \
pid_t pid);
char	*ft_strtok(char *str, const char *sep);
char	*get_path_env(t_data *ms_data, char *command);
int		build_full_path(char *full_path, const char *dir, const char *command);
int		is_valid_dir_token(char *dir);
int		is_duplicate_dir(char *dir, char **dirs, int count);
void	init_shell(t_data **ms_data, char ***my_envs, int return_code);
void	handle_input(t_data *ms_data, char ***my_envs, int *return_code);
void	handle_empty_input(t_data *ms_data, char **my_envs);
void	execute_tree(t_data *ms_data, t_exec *exec_cmd, int *status);
void	exit_minishell(t_data *ms_data, char **my_envs);
void	free_and_copy_environment(char ***my_envs, char **variables);
int		delete_remain_expander(char **variables, int len);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strcpy(char *dest, const char *src);
int		ft_isdigit_exit(int c);
void	handle_exec_errors(char *path, t_data *ms_data);
int		check_options(char **argv, t_data *ms_data);
int		check_options_built_ins(char **argv, t_data *ms_data);
int		check_options_echo(char **argv, t_data *ms_data);
int		ft_is_char_opt(int c);
int		check_options_env(char **argv, t_data *ms_data);
void	build_full_path_2(char *full_path, const char *dir, \
const char *command);
void	signal_child(int sig);
void	ignore_child(int sig);
long	ft_strtol(const char *str, char **endptr);
void	check_print_exit(void);
long	ft_strtol_helper(char *str, long result, int sign);
void	ft_exec_builtin_3(char **argv, t_data *ms_data, char *pwd);
void	handle_variable(char **argv, t_data *ms_data, int i);
void	ft_cmd_not_found_error(char *command, t_data *ms_data, int exit_code);
void	prepare_pipe_error(char *error, t_data *ms_data, int error_code);
void	print_exec(t_cmd *node);
void	print_redir(t_cmd *node);
void	print_pipe(t_cmd *node);
void	print_tree(t_cmd *node);
void	handle_wif(t_data *ms_data, int *status);
void	update_codes_130(t_data *ms_data, int *return_code);
int		ft_is_str(char *str);
int		check_required_args(char *arg, t_data *ms_data, long num);
int		check_options_exit(char **argv, t_data *ms_data);
int		check_2_in_1(char *arg);
int		str_is_white(char *str);
void	signal_child_handler(int sig, t_data *ms_data, int parent_pid);
int		ft_count_args(char **argv);
int		ft_is_special_char(char *arg);
int		check_special_char(int c);
int		is_valid_nbr(char *str);
void	handle_sigquit(int sig);
void	wait_pipe_children(pid_t pid_left, pid_t pid_right, t_data *ms_data);
void	handle_pipe_fork(t_pipe *pipe_cmd, t_data *ms_data, int *pipe_fd);
void	end_this(int status_right, t_data *ms_data);
void	from_child(t_data *ms_data, int parent_pid);
void	from_parent(int local_status, t_data *ms_data);
void	signals_exec_tree(t_data *ms_data, int parent_pid);
void	case_sigquit(int parent_pid, t_data *ms_data, int sig_tmp, \
t_data *ms_data_tmp);
void	prepare_exit_numeric(char *str, char **argv, t_data *ms_data, \
int return_code);
char	*check_final_finder(char *path_env, char *path, char *full_path, \
int code);

#endif
