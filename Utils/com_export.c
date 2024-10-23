/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:18:12 by alfreire          #+#    #+#             */
/*   Updated: 2024/10/23 01:03:47 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_export(t_minish *ms)
{
	int		i;
	char	*equals_sign;

	i = 0;
	while (ms->env_list[i])
	{
		equals_sign = ft_strchr(ms->env_list[i], '=');
		if (equals_sign)
			printf("declare -x %s\n", ms->env_list[i]);
		else
			printf("declare -x %s=\"\"\n", ms->env_list[i]);
		i++;
	}
}

void	add_or_update_env(char ***target_env, const char *assignment)
{
	int		index;

	index = find_env_index(*target_env, assignment);
	if (index != -1)
	{
		free((*target_env)[index]);
		(*target_env)[index] = ft_strdup(assignment);
	}
	else
		add_new_env(target_env, assignment);
}

void	handle_no_assignment(t_minish *ms, char *arg)
{
	char	*empty_assign;

	if (find_env_in_tmp(ms, arg))
		add_or_update_env(&ms->env_tmp, arg);
	else
	{
		empty_assign = malloc(ft_strlen(arg) + 2);
		if (!empty_assign)
			return ;
		ft_strlcpy(empty_assign, arg, ft_strlen(arg) + 1);
		ft_strlcat(empty_assign, "=", ft_strlen(arg) + 2);
		add_or_update_env(&ms->env_list, empty_assign);
		free(empty_assign);
	}
}

void	handle_assignment(t_minish *ms, char *arg)
{
	char	*key;

	key = extract_key(arg);
	if (find_env_in_tmp(ms, key))
		remove_from_tmp(ms, key);
	free(key);
	add_or_update_env(&ms->env_list, arg);
}

void	export(char **exp_args, t_minish *ms)
{
	int	i;

	i = 0;
	if (!exp_args[0])
		print_export(ms);
	while (exp_args[i])
	{
		if (ft_strchr(exp_args[i], '='))
			handle_assignment(ms, exp_args[i]);
		else
			handle_no_assignment(ms, exp_args[i]);
		i++;
	}
}
