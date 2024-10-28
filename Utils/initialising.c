/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialising.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/10/28 11:08:11 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*void	_ms_init(char **envp)
{
	ft_bzero(ms(), sizeof(t_ms));
	(ms()->envlist) = envlist(envp);
	update_envs();
	(ms()->exit_status) = 0;
	(ms()->cwd) = getcwd(NULL, 4096);
	(ms()->in_fd) = STDIN_FILENO;
	(ms()->out_fd) = STDOUT_FILENO;
	return ;
}*/

// static char	*trim_name(char *to_trim)
// {
// 	char	*trimmed;

// 	trimmed = ft_strdup(ft_strchr(to_trim, '=') + 1);
// 	free(to_trim);
// 	to_trim = NULL;
// 	return (trimmed);
// }

static char *trim_name(char *to_trim)
{
    char    *trimmed;
    char    *equal_sign;

    // Verifique se to_trim não é NULL e contém o caractere '='
    if (!to_trim || !(equal_sign = ft_strchr(to_trim, '=')))
    {
        printf("Error: Invalid string passed to trim_name.\n");
        free(to_trim); // Libere a string original, se necessário
        return NULL;
    }

    // Duplicar a parte após o '='
    trimmed = ft_strdup(equal_sign + 1);
    free(to_trim); // Libere a string original após a duplicação
    return (trimmed);
}

void	init_ms(t_minish *ms, char **envp)
{
	int	i;
	int	env_len;

	i = 0;
	env_len = 0;
	ms->env_list = ft_matrix_dup(envp);
	ms->env_tmp = ft_matrix_dup(envp);
	while (ms->env_list[env_len] != NULL)
		env_len++;
	while (i < env_len)
	{
		ms->env_list[i] = trim_name(ft_strdup(ms->env_list[i]));
		i++;
	}
	ms->cwd = getcwd(NULL, 4096);
	ms->fd_in = 0;
	ms->fd_out = 1;
}
