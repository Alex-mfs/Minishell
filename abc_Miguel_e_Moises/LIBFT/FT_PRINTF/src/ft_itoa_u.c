/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:34:50 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:34:52 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
// Converts an unsigned integer into a string

static size_t	itoa_len(unsigned int n)
{
	size_t			len;
	unsigned int	n2;

	len = 1;
	n2 = n;
	while ((n2 / 10) != 0)
	{
		len++;
		n2 = n2 / 10;
	}
	return (len);
}

static char	*itoa_str(unsigned int n, char *nstr, size_t len)
{
	unsigned int	n2;

	n2 = n;
	if (n == 0)
		nstr[0] = '0';
	nstr[len] = '\0';
	while (n2 != 0)
	{
		len--;
		nstr[len] = n2 % 10 + '0';
		n2 = n2 / 10;
	}
	return (nstr);
}

char	*ft_itoa_u(unsigned int n)
{
	size_t			len;
	char			*nstr;

	len = itoa_len(n);
	nstr = (char *)malloc((len + 1) * sizeof(char));
	if (nstr == NULL)
		return (NULL);
	nstr = itoa_str(n, nstr, len);
	return (nstr);
}
