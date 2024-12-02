/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:34:39 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:34:42 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
// Returns a pointer to a new integer which is a duplicate of the given integer.

int	*ft_intdup(int n)
{
	int	*n2;

	n2 = (int *)malloc(sizeof(int));
	if (n2 != NULL)
	{
		*n2 = n;
		return (n2);
	}
	return (NULL);
}
