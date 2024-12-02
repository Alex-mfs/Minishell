/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:45:45 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:45:48 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Outputs the character c to the given file descriptor
#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
