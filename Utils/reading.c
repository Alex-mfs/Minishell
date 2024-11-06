/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/06 15:39:06 by alfreire         ###   ########.fr       */
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

void	print_token_list(t_minish *ms)//ALEX
{
    t_token *curr = ms->tk_list;
    while (curr)
    {
        printf("Token: %s, Tipo: %d\n", curr->token, curr->type);
        curr = curr->next;
    }
}//ALEX

static void	compute(t_minish *ms, char *input)
{
	t_token	*buff; //PARA TESTES
	t_ast	*buff2; //PARA TESTES
	int		i; //PARA TESTES
	int		j; //PARA TESTES

	if (!validate_quotes(input)) //WIP Implementar exit_status
		return ;
	get_tokens(ms, input); //WIP Verificar que "|<" funciona...
	//print_token_list(ms); //ALEX
	//TESTE TOKEN //JOAO
	buff = ms->tk_list;
	i = 0;
	while (buff)
	{
		printf("Token %d: %s [Type %d] [Merge:%d]\n", i, buff->token, buff->type, buff->to_merge);
		buff = buff->next;
		i++;
	}
	printf("\n");
	//END TESTE TOKEN //JOAO
	if (!validate_tokens(ms)) //WIP Implementar exit_status
		return ;
	expand(ms);
	parse(ms);
	//TESTE CMD //JOAO
	buff2 = ms->cmd_list;
	i = 0;
	while (buff2)
	{
		printf("Node %d: cmd=%s\n", i, buff2->cmd);
		j = 0;
		while (buff2->args[j])
		{
			printf("\tArg %d: %s\n", j, buff2->args[j]);
			j++;
		}
		if (buff2->left)
			printf("\t\tRedirect %d: %s %s\n", i, buff2->left->cmd, buff2->left->args[0]);
		if (buff2->right)
			printf("\t\tRedirect %d: %s %s\n", i, buff2->right->cmd, buff2->right->args[0]);
		buff2 = buff2->next;
		i++;
	}
	printf("\n");
	//END TESTE CMD //JOAO
	//printf("chegou aqui.\n"); //ALEX
	if (!assign_var(ms))
	{
		printf("TestAA\n\n"); //JOAO
		execute(ms);
		printf("TestBB\n"); //JOAO
	}
	sanitize_envp(ms);
	unlink("heredoc_tmp");
}

static char	*maintain_prompt(char *cwd)
{
	char	*prompt;
	char	*suffix;

	prompt = ft_strdup("\033[1m""\033[34m""Curr.Directory:""\033[0m""\033[34m");
	if (!prompt)
		return (NULL);
	suffix = ft_strdup("\033[0m""\n""\033[4m""\033[97m""Input minishell:""\033[0m");
	if (!suffix)
	{
		free(prompt);
		return (NULL);
	}
	prompt = ft_strbuild(prompt, cwd);
	if (!prompt)
	{
		free(suffix);
		return (NULL);
	}
	prompt = ft_strbuild(prompt, suffix);
	free(suffix);
	return (prompt);
}

void	read_inputs(t_minish *ms)
{
	char	*prompt;
	char	*input;

	while (1)
	{
		prompt = maintain_prompt(ms->cwd);
		input = readline(prompt);
		if (!input)
		{
			ft_error_msg("Input allocation error.\nExiting minishell\n");
			sanitize_ms(ms, true);
			break ;
		}
		add_history(input);
		compute(ms, input);
		free(input);
		free(prompt);
		sanitize_ms(ms, false);
	}
	rl_clear_history();
}
