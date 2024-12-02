/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:49:22 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/19 14:53:59 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_env(char **argv, t_data *ms_data)
{
	int			i;

	i = 0;
	if (argv[1])
	{
		prepare_error("too many arguments", "env", ms_data, 2);
		return ;
	}
	while (ms_data->variables[i])
	{
		ft_putstr_fd(ms_data->variables[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}
