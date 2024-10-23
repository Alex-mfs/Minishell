/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/10/23 12:20:47 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	assign_var(t_minish *ms)
{
	int		i;
	char	*str;

	i = -1;
	if (ms->tk_list->token && ms->tk_list->token[0])
	{
		str = ms->tk_list->token;
		if (str[0] == '='
			|| str[ft_strlen(str) - 1] == '=')
		{
			error("minishell: bad assignment \n", 1);
			return (false);
		}
		while (str[++i])
		{
			if (str[i] == '=')
			{
				add_or_update_env(&ms->env_tmp, str);
				return (true);
			}
		}
	}
	return (false);
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
	printf("TestReading0: %s\n", ms->tk_list->token);
	printf("TestReading1: %s\n", ms->tk_list->next->token);
	if (!validate_tokens(ms)) //WIP na verdade, é permitido terminar num pipe. Corrigir.
		return ;
	expand(ms); //WIP Falta estudar questao do merge.
	parse(ms);
	if(!assign_var(ms)) //WIP Se houver variável para atribuir valor (ex.: BUFFER_SIZE=40), faz-se. Senão, apenas executar (espera, porque senão?)
		execute(ms); //WIP Executar cada um dos comandos
	//WIP sanitize_envp(ms); //WIP actualizar env_list e...path? Porque actualizar env_list?
	//WIP unlink(HEREDOC) delete any heredoc file
}

//static char	*maintain_prompt(char *cwd)
//{
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
	//char	*prompt;
	//char	*suffix;

	//prompt = /*Formatacao prefixo*/"Curr.Directory:"/*Formatacao cwd*/;
	//prompt = "\033[1m""\033[32m""Curr.Directory:""\033[0m""\033[32m"; //Bold Green, then regular green
	//suffix = /*Reset a formatacao cwd*//*Formatacao sufixo*/ "Input minishell:" /*Reset formatacao*/;
	//suffix = "\033[0m""\n""\033[4m""\033[97m""Input minishell:""\033[0m";
	//prompt = ft_strbuild(prompt, cwd); //Potential memory issue? Test with valgrind
	//prompt = ft_strbuild(prompt, suffix);
	//return (prompt);
	//prefix + cwd + suffix
	//formatacao do prompt está aberta para discussão
//}

static char	*maintain_prompt(char *cwd)
{
	char	*prompt;
	char	*suffix;

	// Duplicar a string literal para que ela seja alocada dinamicamente
	prompt = ft_strdup("\033[1m""\033[32m""Curr.Directory:""\033[0m""\033[32m"); // Bold Green, then regular green
	if (!prompt)
		return (NULL);

	// Duplicar a string suffix para garantir que ela possa ser concatenada e liberada
	suffix = ft_strdup("\033[0m""\n""\033[4m""\033[97m""Input minishell:""\033[0m");
	if (!suffix)
	{
		free(prompt); // Liberar prompt caso suffix falhe
		return (NULL);
	}

	// Concatenar o prompt com o cwd e, em seguida, com o suffix
	prompt = ft_strbuild(prompt, cwd); // Agora a string 'prompt' foi alocada dinamicamente
	if (!prompt)
	{
		free(suffix);
		return (NULL);
	}

	prompt = ft_strbuild(prompt, suffix); // Concatenar o sufixo
	free(suffix); // Liberar o suffix, pois já foi concatenado
	return (prompt);
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
			sanitize_ms(ms, true); //with exit // fazer algo parecido mas retornar para o main para finalizar;
			break ;
		}
		add_history(input);
		compute(ms, input); //WIP execute/compute input
		free(input);
		free(prompt);
		sanitize_ms(ms, false); //without exit
	}
	rl_clear_history();
}
