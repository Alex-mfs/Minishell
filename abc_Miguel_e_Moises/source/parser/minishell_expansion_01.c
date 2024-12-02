/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expansion_01.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:17:01 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/24 05:59:44 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// GET VARIABLE NAME
static int	getvarname(t_data *ms_data, char **start, char *end, \
char **var_name)
{
	char	*var_start;
	char	*var_end;

	var_start = *start;
	while (*start != end && ft_strchr(MS_VAR_CHAR, **start))
		(*start)++;
	var_end = *start;
	if (var_start < var_end)
	{
		*var_name = check_str(ms_data, substr(var_start, var_end));
		if (!*var_name)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// GET RETURN CODE
static char	*get_return_code(t_data *ms_data, char *start, char **str)
{
	char	*ret_str;

	ret_str = check_str(ms_data, ft_itoa(ms_data->return_code));
	if (ret_str)
		*str = check_str(ms_data, concat_str(*str, ret_str, ret_str + \
		ft_strlen(ret_str)));
	free(ret_str);
	start++;
	return (start);
}

// EXPAND VARIABLE
char	*expand_var(t_data *ms_data, char *start, char *end, char **str)
{
	char	*var_name;
	char	*var;

	start++;
	if (*start == '?')
		return (get_return_code(ms_data, start, str));
	var_name = NULL;
	if (getvarname(ms_data, &start, end, &var_name) == EXIT_FAILURE)
	{
		*str = free_str(*str);
		return (start);
	}
	if (!var_name)
	{
		if (ft_strchr(MS_QUOTES, *start) && *start != '\0')
			return (start);
		*str = check_str(ms_data, concat_str(*str, start - 1, start));
		return (start);
	}
	var = my_getenv_expans(var_name, ms_data->variables);
	free(var_name);
	if (var)
		*str = check_str(ms_data, concat_str(*str, var, var + ft_strlen(var)));
	return (start);
}
