/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:49:40 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/25 20:46:28 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_unset(char **argv, t_data *ms_data)
{
	int	i;
	int	index;

	ms_data->return_code = 0;
	i = 1;
	if (argv[i] == NULL)
	{
		ms_data->return_code = 0;
		return ;
	}
	while (argv[i])
	{
		index = find_variable(ms_data->variables, argv[i]);
		if (index != -1)
			ms_data->variables = reduce_environment(ms_data->variables, \
			argv[i], ms_data);
		i++;
	}
}
