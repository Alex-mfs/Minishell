/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:45:30 by alfreire          #+#    #+#             */
/*   Updated: 2024/10/05 18:23:56 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <time.h>
//# include <readline/readline.h>
//# include <readline/history.h>
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
	char			**env_list;
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
//Utils - Handling
void	handle_interrupt(int signum);
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

//minishell.c - exit_status
void	set_exit_status(int status);
int		get_exit_status(void);

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