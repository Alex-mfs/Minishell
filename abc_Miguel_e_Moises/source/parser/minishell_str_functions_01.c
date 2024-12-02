/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_str_functions_01.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:32:33 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/24 05:52:06 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// CREATE A SUBSTRING FROM POINTER START TO POINTER END
char	*substr(char *start, char *end)
{
	int		i;
	char	*str;

	str = (char *)malloc((end - start + 1) * sizeof(char));
	if (str)
	{
		i = 0;
		while (start < end)
		{
			str[i] = *start;
			start++;
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}

// CONCATENATE STRINGS 
char	*concat_str(char *str, char *sub_start, char *sub_end)
{
	char	*str2;
	char	*str3;

	str2 = substr(sub_start, sub_end);
	if (!str2)
		return (free_str(str));
	if (!str)
		return (str2);
	str3 = ft_strjoin(str, str2);
	free(str);
	free(str2);
	return (str3);
}
