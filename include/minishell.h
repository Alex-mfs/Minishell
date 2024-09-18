/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:45:30 by alfreire          #+#    #+#             */
/*   Updated: 2024/09/16 19:33:16 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <signal.h>
# include <time.h>
//# include <readline/readline.h>
//# include <readline/history.h>
//# include <sys/types.h>
//# include <sys/wait.h>
# include "../libft/libft.h"

typedef struct s_ast
{
	int				index;
	char			*cmd;
	char			**args;
	struct s_ast	*left;
	struct s_ast	*right;
}			t_ast;

typedef struct s_token
{
	char	*token;
	t_lexer	type;
	t_token	*next;
}			t_token;

typedef struct s_minish
{
	int				**pipes;
	char			**env_list;
	char			*cwd;
	struct s_token	*tk_list;
	struct s_ast	*cmd_list;
}			t_minish;

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

#endif