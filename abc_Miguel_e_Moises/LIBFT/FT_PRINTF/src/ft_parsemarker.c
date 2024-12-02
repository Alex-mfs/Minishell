/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsemarker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:35:23 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:35:30 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
// Parses the format string and calls the necessary functions to create the
// output string for printf function.

int	ft_parsemarker(const char *format, unsigned int *i, \
		t_list **lst, va_list ap)
{
	int	state;

	*i = *i + 1;
	state = ft_type(format, i, lst, ap);
	return (state);
}
