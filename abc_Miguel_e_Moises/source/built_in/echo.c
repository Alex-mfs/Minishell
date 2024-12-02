/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:49:19 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/30 16:17:36 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_echo(char **argv)
{
	int		i;
	int		print_newline;

	i = 1;
	print_newline = 1;
	if (!argv[1])
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	if (argv[1] && !ft_strncmp(argv[1], "-n", 3))
	{
		while (argv[i] && !ft_strncmp(argv[i], "-n", 3))
			i++;
		print_newline = -1;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (print_newline == 1)
		ft_putstr_fd("\n", 1);
}
