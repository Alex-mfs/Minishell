/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/11/21 16:47:33 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*static void	print_tree(t_ast *node) //JOAO
{
	printf("Passando por Node Index %d: cmd=%s, arg[0]=%s\n", node->index, node->cmd, node->args[0]);
	if (node->left)
		printf("\tNó Esquerda: Index=%d, cmd=%s, arg[0]=%s\n", node->left->index, node->left->cmd, node->left->args[0]);
	if (node->right)
		printf("\tNó Direita: Index=%d, cmd=%s, arg[0]=%s\n", node->right->index, node->right->cmd, node->right->args[0]);
	if (node->left)
		print_tree(node->left);
	if (node->right)
		print_tree(node->right);
	printf("\t\tResolvendo o Node Index %d: cmd=%s, arg[0]=%s\n", node->index, node->cmd, node->args[0]);
} //JOAO*/

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
			return (true);
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
	//t_token	*buff; //PARA TESTES
	//t_ast	*buff2; //PARA TESTES
	//int		i; //PARA TESTES
	//int		j; //PARA TESTES

	if (!validate_quotes(input)) //WIP Implementar exit_status
		return ;
	get_tokens(ms, input);
	/*//TESTE TOKEN //JOAO
	buff = ms->tk_list;
	i = 0;
	while (buff)
	{
		printf("Token %d: %s [Type %d] [Merge:%d]\n", i, buff->token, buff->type, buff->to_merge);
		buff = buff->next;
		i++;
	}
	printf("\n");
	//END TESTE TOKEN //JOAO*/
	if (!validate_tokens(ms)) //WIP Implementar exit_status
		return ;
	expand(ms);
	/*//TESTE TOKEN //JOAO
	buff = ms->tk_list;
	i = 0;
	while (buff)
	{
		printf("Token %d: %s [Type %d] [Merge:%d]\n", i, buff->token, buff->type, buff->to_merge);
		buff = buff->next;
		i++;
	}
	printf("\n");
	//END TESTE TOKEN //JOAO*/
	parse(ms);
	/*//TESTE CMD //JOAO
	print_tree(lastpipe(ms->cmd_list));
	printf("\n");
	//END TESTE CMD //JOAO*/
	if (!assign_var(ms))
		execute(ms);
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
	suffix = ft_strdup("\033[0m""\n""\033[4m""\033[97m" \
			"Input minishell:""\033[0m");
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
