/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dec2hexptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:34:28 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:34:32 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
// Returns a string representing a size_t number in hexadecimal format.
// Outputs hexadecimal number in lower case (default) or upper case.

static size_t	ft_hexlen(size_t n)
{
	size_t	len;

	len = 0;
	while (n > 0)
	{
		len++;
		n = n / 16;
	}
	if (len > 0)
		len = len + 3;
	return (len);
}

static char	*ft_dict(char type, char *str)
{
	char	*dict;

	if (type == 'u')
	{
		str[1] = 'X';
		dict = "0123456789ABCDEF";
	}
	else
	{
		str[1] = 'x';
		dict = "0123456789abcdef";
	}
	return (dict);
}

char	*ft_dec2hexptr(size_t n, char type)
{
	char	*str;
	char	*dict;
	size_t	len;
	int		i;

	len = ft_hexlen(n);
	if (len == 0)
		return (NULL);
	str = (char *)malloc((len) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = '0';
	dict = ft_dict(type, str);
	i = 2;
	while (n > 0 && (size_t)i < (len - 1))
	{
		str[len - i] = dict[n % 16];
		n = n / 16;
		i++;
	}
	str[len - 1] = '\0';
	return (str);
}
