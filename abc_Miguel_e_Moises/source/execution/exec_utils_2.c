/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:16:03 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/25 16:16:22 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_dir_token(char *dir)
{
	if (!dir || dir[0] == '\0')
		return (0);
	return (!(ft_strcmp(dir, ".") == 0 || ft_strcmp(dir, "..") == 0 || \
	ft_strcmp(dir, "/") == 0 || ft_strcmp(dir, "//") == 0 || \
	ft_strcmp(dir, "/.") == 0 || ft_strcmp(dir, "/..") == 0));
}

int	is_duplicate_dir(char *dir, char **dirs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (ft_strcmp(dir, dirs[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
