/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialising.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/07/24 15:05:29 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*trim_name(char *to_trim)
{
	int		i;
	char	*trimmed;

	i = 0;
	trimmed = ft_strdup(ft_strchr(to_trim, '=') + 1);
	free(to_trim);
	return (trimmed);
}

void	init_ms(t_minish *ms, char **envp)
{
	int	i;

	i = 0;
	ms->env_list = ft_strarrdup(envp);
	while (i < 50)
	{
		ms->env_list[i] = trim_name(ms->env_list[i]);
		i++;
	}
}
