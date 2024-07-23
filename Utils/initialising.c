/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialising.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/07/23 14:27:06 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_ms(t_minish *ms, char **envp)
{
	ms->env_list = ft_strarrdup(envp);
	// WIP Guardar apenas as variaveis, nao as strings inteiras
}
