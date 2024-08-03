/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:45:30 by alfreire          #+#    #+#             */
/*   Updated: 2024/07/30 16:24:54 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <signal.h>
# include <time.h>
//# include <readline/readline.h>
//# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_token
{
	char	*token;
	t_lexer	type;
	t_token	*next;
}			t_token;

typedef struct s_minish
{
	char			**env_list;
	char			*cwd;
	struct s_token	*tk_list;
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
//Utils - Lexing
void	lexer(t_minish *ms, char *input);

#endif