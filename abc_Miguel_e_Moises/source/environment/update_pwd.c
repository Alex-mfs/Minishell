/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:36:45 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/11/28 12:21:33 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_pwd(char *old_pwd, t_data *ms_data)
{
	char	*new_pwd;
	char	*old_pwd_str;
	char	*new_pwd_str;

	old_pwd_str = NULL;
	new_pwd_str = NULL;
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		print_exec_error(strerror(errno), "getcwd");
		ms_data->return_code = 1;
		free(old_pwd);
		return ;
	}
	new_pwd_str = ft_strjoin("PWD=", new_pwd);
	update_new_pwd(new_pwd, new_pwd_str, ms_data);
	old_pwd_str = ft_strjoin("OLDPWD=", old_pwd);
	update_old_pwd(old_pwd, old_pwd_str, ms_data);
	ms_data->return_code = 0;
}

void	update_old_pwd(char *old_pwd, char *old_pwd_str, t_data *ms_data)
{
	if (find_variable(ms_data->variables, "OLDPWD") == -1)
		ms_data->variables = expand_environment(ms_data->variables, \
		old_pwd_str, ms_data);
	else
	{
		ms_data->variables = reduce_environment(ms_data->variables, \
		"OLDPWD", ms_data);
		ms_data->variables = expand_environment(ms_data->variables, \
		old_pwd_str, ms_data);
	}
	free(old_pwd_str);
	free(old_pwd);
}

void	update_new_pwd(char *new_pwd, char *new_pwd_str, t_data *ms_data)
{
	if (find_variable(ms_data->variables, "PWD") == -1)
		ms_data->variables = expand_environment(ms_data->variables, \
		new_pwd_str, ms_data);
	else
	{
		ms_data->variables = reduce_environment(ms_data->variables, \
		"PWD", ms_data);
		ms_data->variables = expand_environment(ms_data->variables, \
		new_pwd_str, ms_data);
	}
	free(new_pwd_str);
	free(new_pwd);
}
