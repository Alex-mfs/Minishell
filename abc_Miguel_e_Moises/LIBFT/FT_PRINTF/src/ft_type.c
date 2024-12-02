/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:36:22 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:36:24 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
// Parses the marker type for printf function.

int	ft_type(const char *format, unsigned int *i, t_list **lst, va_list ap)
{
	int	state;

	if (format[*i] == 'c')
		state = ft_type_c(lst, ap);
	if (format[*i] == 's')
		state = ft_type_s(lst, ap);
	if (format[*i] == 'p')
		state = ft_type_p(lst, ap);
	if (format[*i] == 'd' || format[*i] == 'i')
		state = ft_type_di(lst, ap);
	if (format[*i] == 'u')
		state = ft_type_u(lst, ap);
	if (format[*i] == 'x')
		state = ft_type_x(lst, ap, 'l');
	if (format[*i] == 'X')
		state = ft_type_x(lst, ap, 'u');
	if (format[*i] == '%')
		state = ft_type_perc(lst);
	return (state);
}
