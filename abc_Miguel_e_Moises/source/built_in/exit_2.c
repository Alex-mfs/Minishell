/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:19:43 by madao-da          #+#    #+#             */
/*   Updated: 2024/11/30 16:21:47 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	str_is_white(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (1);
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int	ft_is_special_char(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (check_special_char(arg[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	check_special_char(int c)
{
	if (c >= 33 && c <= 47)
	{
		if (c == 34 || c == 39)
			return (0);
		return (1);
	}
	else if (c >= 58 && c <= 64)
		return (1);
	else if (c >= 91 && c <= 96)
		return (1);
	else if (c >= 123 && c <= 126)
		return (1);
	return (0);
}

int	is_valid_nbr(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
	{
		if (str[1] == '\0')
			return (0);
	}
	if (str[0] == '+' || str[0] == '-')
	{
		i++;
		while (str[i])
		{
			if (str[i] < '0' || str[i] > '9')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}
