/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wip_ms_djesus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:45:30 by alfreire          #+#    #+#             */
/*   Updated: 2024/07/29 17:00:46 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*MINISHELL (structure)*/

typedef struct s_ms
{
	int		in_fd;
	int		out_fd;
	int		exit_status;
	int		num_commands;
	bool	in_heredoc;
	char	*cwd;
	char	*input;
	char	*prompt;
	char	**path;
	char	**envp;
	int		**pipes;
	t_list	*envlist;
	t_list	*envtmp;
	t_list	*lexemes;
	t_ast	*ast;
}	t_ms;

/*ENV (structures)*/

typedef struct s_env
{
	char			*key;
	char			*value;
}	t_env;

/*LEXER (structures)*/

typedef enum e_lexeme
{
	LEX_IN_1,
	LEX_OUT_1,
	LEX_IN_2,
	LEX_OUT_2,
	LEX_PIPE,
	LEX_SINGLE_QUOTES,
	LEX_DOUBLE_QUOTES,
	LEX_TERM,
}	t_lexeme;

typedef struct s_token
{
	char			*str;
	bool			can_merge;
	t_lexeme		type;
}	t_token;

/*PARSER (structures)*/

typedef enum e_operation
{
	READ,
	NEXT,
	LOOKAHEAD,
	RESET
}	t_operation;

typedef struct s_ast
{
	t_token			*token;
	char			**args;
	int				index;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

/*MACROS*/

//! Colours
# define ANSI_BLACK		"\033[30m"
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
# define ANSI_UNDERLINE	"\033[4m"

//! Errors
# define ERROR_UNKNOWN_CMD		"minishell: command not found: "
# define ERROR_UNKNOWN_FILE		"minishell: no such file or directory: "
# define ERROR_DIRECTORY		"minishell: that's a directory: "
# define ERROR_NO_PERMISSIONS	"minishell: permission denied: "
# define ERROR_BAD_ASSIGNMENT	"minishell: bad assignment "
# define ERROR_SYNTAX			"minishell: syntax error near unexpected token "
# define ERROR_UNCLOSED_RED		"minishell: unclosed redirection"
# define ERROR_UNCLOSED_PIPES	"minishell: unclosed pipes"
# define ERROR_UNCLOSED_QUOTES	"minishell: unclosed quotes"

# define ERROR_CD_WRONG_DIR		"cd: no such file or directory: "
# define ERROR_CD_MANY_ARGS		"cd: too many arguments"
# define ERROR_CD_NO_HOME		"cd: HOME not set"

# define ERROR_EXIT_NO_NUM		"exit: numeric argument required"
# define ERROR_EXIT_MANY_ARGS	"exit: too many arguments"

# define ERROR_ENV_UNKNOWN_FILE	"env: no such file or directory: "

//! Lexer symbols
# define SYMBOLS	"<>\'\"| "
# define QUOTES		"\'\""
# define SPECIAL	"<>| "

//! Minishell
# define PROMPT_UPPER	"┎─── "
# define PROMPT_LOWER	"┖─ minishell ❯ "

//! Pipes indexes
# define READ_END 	0
# define WRITE_END 	1

//! Heredoc temporary file
# define HEREDOC	"heredoc.tmp"

//! debug
# define DEBUG
// # define HERE		printf("HERE\n");

