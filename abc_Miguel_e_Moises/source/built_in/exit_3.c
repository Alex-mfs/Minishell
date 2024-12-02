/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:20:41 by madao-da          #+#    #+#             */
/*   Updated: 2024/11/30 16:21:04 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	prepare_to_exit(t_data *ms_data, char *pwd, int exit_code)
{
	clean_shell(ms_data);
	free(pwd);
	exit(exit_code);
}

int	ft_isdigit_exit(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int	ft_is_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit_exit(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	check_required_args(char *arg, t_data *ms_data, long num)
{
	(void)ms_data;
	if (is_valid_nbr(arg) == 1)
		return (0);
	if (str_is_white(arg) == 1)
		return (1);
	if (ft_is_str(arg) == 1)
		return (1);
	if (num > LONG_MAX || num < LONG_MIN)
		return (1);
	if (!ft_strncmp(arg, "--", 2) && ft_strlen(arg) < 2)
		return (1);
	if (ft_is_special_char(arg) == 1)
		return (1);
	return (0);
}

int	check_2_in_1(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == ' ' && arg[i + 1] != '\0')
			return (1);
		i++;
	}
	return (0);
}
