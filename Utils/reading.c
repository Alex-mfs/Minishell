/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/07/29 17:43:52 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	assign_var(t_minish *ms)
{
	/*int	i;

	i = -1;
	if (token->str[0])
	{
		if (token->str[0] == '='
			|| token->str[ft_strlen(token->str) - 1] == '=')
		{
			error(ANSI_RED, ERROR_BAD_ASSIGNMENT, NULL, 1);
			return (false);
		}
	}
	while (token->str[++i])
	{
		if (token->str[i] == '=')
		{
			export_directly(&ms()->envtmp, token->str);
			return (true);
		}
	}
	return (false);*/
}

static void	compute(t_minish *ms, char *input)
{
	/*if (!lexical_analysis())
		return (0);
	lexer();
	if (!syntatic_analysis())
		return (0);
	expander();
	parser();
	if (!is_assignment(ms()->lexemes->content))
		execute(ms()->ast);
	update_envs();
	unlink(HEREDOC);
	return (0);*/
	if (!validate_quotes(input))
		return ;
	get_tokens(ms, input); //WIP mergeable? what is merge?
	if (!validate_tokens(ms))
		return ;
	expand(ms); //WIP Lida com inputs tipo $. Incompleto.
	parse(ms); //WIP Distingue comandos de argumentos. Define pipes. Muito incompleto.
	//WIP if(!assign_var(ms)) Se houver variável para atribuir valor (ex.: BUFFER_SIZE=40), faz-se. Senão, apenas executar
	//WIP execute(ms);//WIP Executar cada um dos comandos
	//WIP sanitize envp & path
	//WIP unlink() delete any heredoc file
}

static char	*maintain_prompt(t_minish *ms)
{
	//# define PROMPT_UPPER	"┎─── "
	//# define PROMPT_LOWER	"┖─ minishell ❯ "
	/*char	*tmp;
	char	*prompt;
	char	*prefix;
	char	*suffix;

	prefix = ANSI_BOLD""ANSI_WHITE""PROMPT_UPPER""ANSI_UNDERLINE""ANSI_CYAN;
	suffix = ANSI_RST"\n"ANSI_WHITE""PROMPT_LOWER""ANSI_RST;
	tmp = ft_strjoin(prefix, ms()->cwd); //current working directory
	prompt = ft_strjoin(tmp, suffix);
	free(tmp);
	return (prompt);*/
	char	*prompt;
	char	*suffix;

	prompt = /*Formatacao prefixo*/ "Curr.Directory:" /*Formatacao cwd*/;
	suffix = /*Reset a formatacao cwd*//*Formatacao sufixo*/ "Input minishell:" /*Reset formatacao*/;
	prompt = ft_strbuild(prompt, ms->cwd); //Potential memory issue? Test with valgrind
	prompt = ft_strbuild(prompt, suffix);
	return (prompt);
	//prefix + cwd + suffix
	//WIP definir formatacao do prompt
}

void	read_inputs(t_minish *ms)
{
	/*	while (1)
	{
		(ms()->prompt) = _update_prompt();
		(ms()->input) = readline(ms()->prompt);
		if (!ms()->input)
		{
			printf("exit\n");
			sanitize(true);
		}
		add_history(ms()->input);
		_compute();
		sanitize(false);
	}
	rl_clear_history();*/
	char	*prompt;
	char	*input;

	while (1)
	{
		prompt = maintain_prompt(ms);
		input = readline(prompt); //WIP confirmar os efeitos de readline
		if (!input)
		{
			printf("Input allocation error.\nExiting minishell\n");
			//WIP sanitize(ms); //with exit
		}
		add_history(input);
		compute(ms, input); //WIP execute/compute input
		//WIP sanitize(ms); //without exit
	}
	rl_clear_history();
}
