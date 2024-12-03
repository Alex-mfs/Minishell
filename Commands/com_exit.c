/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:19:22 by alfreire          #+#    #+#             */
/*   Updated: 2024/12/01 23:04:01 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*skip_whitespace(char *str)
{
	while ((*str >= 9 && *str <= 13) || (*str == ' '))
		str++;
	return (str);
}

long long	ft_atoll(char *str, t_minish *ms)
{
	unsigned long long	num;
	int					sign;

	num = 0;
	sign = 1;
	str = skip_whitespace(str);
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		num = num * 10 + (*str++ - '0');
	if (*str)
		error("exit: numeric argument required\n", 2);
	else if ((sign > 0 && num > (unsigned long long)LLONG_MAX) || \
		(sign < 0 && num > (unsigned long long)-(LLONG_MIN)))
		error("exit: numeric argument required\n", num);
	else
		return ((long long)(num * sign));
	sanitize_ms(ms, true);
	return (num);
}

long long	calculate_exit_code(long long num)
{
	num = num % 256;
	if (num < 0)
		num += 256;
	return (num);
}

void	exit_bash(char **exit_args, t_minish *ms, int tmp)
{
	size_t		arg_num;
	long long	num;

	arg_num = 0;
	num = 0;
	while (exit_args[arg_num] && exit_args[arg_num][0])
		arg_num++;
	if (arg_num == 0)
		set_exit_status(tmp);
	else
		num = ft_atoll(exit_args[0], ms);
	if (arg_num > 1)
		return (error("exit: too many arguments\n", 1));
	if (arg_num == 1)
		set_exit_status(calculate_exit_code(num));
	if (lastpipe(ms->cmd_list)->index == 0)
		printf("exit\n");
	sanitize_ms(ms, true);
}
