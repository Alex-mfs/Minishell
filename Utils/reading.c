/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/09/25 19:18:01 by joao-rib         ###   ########.fr       */
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
	if (!validate_tokens(ms)) //WIP na verdade, é permitido terminar num pipe. Corrigir.
		return ;
	expand(ms); //WIP Lida com inputs tipo $. Incompleto.
	//WIP parse(ms); //WIP Distingue comandos de argumentos. Define pipes. Muito incompleto.
	//WIP if(!assign_var(ms)) Se houver variável para atribuir valor (ex.: BUFFER_SIZE=40), faz-se. Senão, apenas executar
	//WIP execute(ms);//WIP Executar cada um dos comandos
	//WIP sanitize envp & path
	//WIP unlink(HEREDOC) delete any heredoc file
}

static char	*maintain_prompt(char *cwd)
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

	//prompt = /*Formatacao prefixo*/"Curr.Directory:"/*Formatacao cwd*/;
	prompt = "\033[1m""\033[32m""Curr.Directory:""\033[0m""\033[32m"; //Bold Green, then regular green
	//suffix = /*Reset a formatacao cwd*//*Formatacao sufixo*/ "Input minishell:" /*Reset formatacao*/;
	suffix = "\033[0m""\n""\033[4m""\033[97m""Input minishell:""\033[0m";
	prompt = ft_strbuild(prompt, cwd); //Potential memory issue? Test with valgrind
	prompt = ft_strbuild(prompt, suffix);
	return (prompt);
	//prefix + cwd + suffix
	//formatacao do prompt está aberta para discussão
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
		prompt = maintain_prompt(ms->cwd);
		input = readline(prompt); //WIP confirmar os efeitos de readline; gera memoryleaks, mas valgrind pode ignorar, investigar
		if (!input) // em caso de ctrl+d
		{
			printf("Input allocation error.\nExiting minishell\n");
			sanitize(ms, true); //with exit // fazer algo parecido mas retornar para o main para finalizar;
			break ;
		}
		add_history(input);
		compute(ms, input); //WIP execute/compute input
		free(input);
		free(prompt);
		sanitize(ms, false); //without exit
	}
	rl_clear_history();
}
