/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/07/25 19:16:23 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	//definir formatacao do prompt
}

void	read_inputs(t_minish *ms)
{
	while (1)
	{
		maintain_prompt(ms);
		//handle input
		//(error handling)
		//register input in history
		//execute/compute input
		//sanitize the structure
	}
	rl_clear_history();
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
}
