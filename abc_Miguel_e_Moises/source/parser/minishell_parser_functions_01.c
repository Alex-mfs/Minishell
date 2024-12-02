/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_functions_01.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madao-da <madao-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:47:14 by madao-da          #+#    #+#             */
/*   Updated: 2024/11/30 18:47:16 by madao-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// PARSE QUOTES
static char	*parse_quotes(t_data *ms_data, char *str, int *token)
{
	char	quote;

	quote = *str;
	str++;
	while (*str != quote)
	{
		if (*str == '\0')
		{
			print_error(ms_data, QUOTE, &quote);
			*token = TOKEN_ERROR;
			return (str);
		}
		str++;
	}
	return (str);
}

// PARSE TEXT
char	*parse_text(t_data *ms_data, char *str, int *token)
{
	*token = TOKEN_TEXT;
	while (*str != '\0' && !ft_strchr(MS_SPACE, *str) && \
	!ft_strchr(MS_TOKENS, *str))
	{
		if (ft_strchr(MS_QUOTES, *str))
		{
			str = parse_quotes(ms_data, str, token);
			if (*token == TOKEN_ERROR)
				return (str);
			if (*str != '\0')
				str++;
		}
		else
			str++;
	}
	return (str);
}
