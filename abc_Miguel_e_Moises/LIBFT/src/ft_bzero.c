/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:41:06 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:41:09 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Replaces the first n characters of a memory area by 0
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
